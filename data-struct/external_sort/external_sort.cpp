#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
#define MAX_INT 0x7fffffff
#define MIN_INT -1

//工作区大小
const int kMaxSize = 1000000;
//最大归并路数
const int kMaxWay = 10;
//工作区
int buffer[kMaxSize];
//堆的大小，堆的大小会改变且小于工作区，用于排除比上次输出小的数据
int heap_size;
int num_of_runs;

struct Run
{
    int *buffer;       //每个归并段的缓存
    int length;     // 缓冲区内元素个数
    int idx;        // 当前所读元素下标
};

//败者树,记录了除叶节点外的位置,也就是记录了败者
//败者树是完全二叉树，所以也可以像堆一样用数组来存
int ls[kMaxWay];
Run *runs[kMaxWay];     //归并段结构

void Swap(int *arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

void Siftdown(int *heap, int pos, int size)
{
    while(pos < size/2)
    {
        int tmp = 2 * pos + 1;
        int rc = 2* pos + 2;
        if((rc < size) && heap[tmp] > heap[rc])
            tmp = rc;
        if(heap[pos] < heap[tmp])
            return;
        Swap(heap, pos, tmp);
        pos = tmp;
    }
}

void BuildHeap(int *heap, int size)
{
    for(int i = size/2-1; i >= 0; i--)
        Siftdown(heap, i, size);
}

// 返回生成归并段的数量
int GenerateRuns(const char *in_file)
{
    ifstream in(in_file);
    char output_file[20];
    ofstream out;
    int i = 0;//工作区中的数据
    int count = 0;//文件计数
    int num;
    
    //往第一个buffer里面读数据？为什么单独拿出来？
    while(!in.eof())
    {
        in >> buffer[i];
        if(++i == kMaxSize) 
            break;
    }
    
    //当工作区满时,一直循环
    while(i == kMaxSize)
    {
        heap_size = kMaxSize;
        count++;
        out.close();
        sprintf(output_file, "%d", count);
        out.open(output_file);
        //把buffer建成堆
        BuildHeap(buffer, heap_size);
        
        //文件还没读完，heap_size是指堆中还有比刚输出的数大的
        while(heap_size != 0 && !in.eof())
        {
            //将最小的输出到文件
            out << buffer[0] << endl;
            //再读入一个
            in >> num;
            
            if(num > buffer[0]){//如果这个数比刚输出的大，放到堆顶
                buffer[0] = num;
            }else{ //如果小,放到堆底，减小堆的大小
                buffer[0] = buffer[heap_size-1];
                buffer[heap_size-1] = num;
                heap_size--;
            }
            Siftdown(buffer, 0, heap_size);
        }
        
        //当文件被读完,减小i，跳出循环
        //将工作区内比上次输出大的数输出
        if(heap_size != 0) {
            i = i - heap_size;
            while(heap_size != 0)
            {
                out << buffer[0] << endl;
                buffer[0] = buffer[--heap_size];
                Siftdown(buffer, 0, heap_size);
            }
        }
    }

    //新起一个文件，将剩余的数输出
    if(i != 0){
        heap_size = i;
        count++;
        out.close();
        sprintf(output_file, "%d", count);
        out.open(output_file);
        int offset = kMaxSize - heap_size;
        BuildHeap(buffer+offset, heap_size);
        while(heap_size != 0)
        {
            out << buffer[offset] << endl;
            buffer[offset] = buffer[--heap_size+offset];
            Siftdown(buffer+offset, 0, heap_size);
        }
        out.close();
    }
    return count;
}

//共n个叶节点，沿着第s个向根的路径调整
void Adjust(Run **runs, int n, int s)
{
    //计算s父节点的编号t,这个计算方式书上没有耶,要记下来
    int t = (s + n) / 2;
    int tmp;

    while(t != 0)
    {
        if(s == -1)
            break;
        //当s比t大时
        if(ls[t] == -1 || runs[s]->buffer[runs[s]->idx] > 
                runs[ls[t]]->buffer[runs[ls[t]]->idx])
        {
            tmp = s;
            s = ls[t];//新的胜者为t
            ls[t] = tmp;//将这次的败者s存到败者树
        }
        //对于完全二叉树，父节点的编号为⌊t/2⌋
        t /= 2;
    }
    ls[0] = s;
}

//败者树有n个叶子节点，runs里是每个叶子节点的内容
void CreateLoserTree(Run **runs, int n)
{
    for(int i = 0; i < n; i++){
        ls[i] = -1;
    }
    //分别沿这n个叶子节点到根的路径调整败者树
    for(int i = n-1; i >= 0; i--){
        Adjust(runs, n, i);
    }
}

void MergeSort(Run **runs, int num_of_runs, const char* file_out)
{
    // 初始化Run
    if(num_of_runs > kMaxWay)
        num_of_runs = kMaxWay;
    int length_per_run = kMaxSize / num_of_runs;
    //
    for(int i = 0; i < num_of_runs; i++)
        runs[i]->buffer = buffer + i * length_per_run;

    //打开文件
    ifstream in[kMaxWay];
    char file_name[20];
    for(int i = 0; i< num_of_runs; i++)
    {
        sprintf(file_name, "%d", i+1);
        in[i].open(file_name);
    }
    // 将归并段文件的数据读到缓冲区中
    for(int i = 0; i < num_of_runs; i++)
    {
        int j = 0;
        //读第i个文件
        while(in[i] >> runs[i]->buffer[j])
        {
            j++;
            if(j == length_per_run)
                break;
        }
        runs[i]->length = j;
        runs[i]->idx = 0;
    }

    //创建败者树
    CreateLoserTree(runs, num_of_runs);
    ofstream out(file_out);
    int live_runs = num_of_runs;
    
    //输出到文件
    while(live_runs > 0){
        //输出败者树中最小的那个归并段中最小的元素
        out << runs[ls[0]]->buffer[runs[ls[0]]->idx++] << endl;
        
        //如果buffer里面的数据用光了，从临时文件读入
        if(runs[ls[0]]->idx == runs[ls[0]]->length)
        {
            int j = 0;
            while(in[ls[0]] >> runs[ls[0]]->buffer[j])
            {
                j++;
                if(j == length_per_run)
                    break;
            }
            runs[ls[0]]->length = j;
            runs[ls[0]]->idx = 0;
        }
        
        //如果归并段内容全都输出了，放一个最大值
        if(runs[ls[0]]->length == 0)
        {
            runs[ls[0]]->buffer[runs[ls[0]]->idx] = MAX_INT;
            live_runs--;
        }
        Adjust(runs, num_of_runs, ls[0]);
    }
}

int main(int argc, char **argv)
{
    if(argc != 2){
        cerr << "请输入要排序的文件名！" << endl;
        exit(1);
    }
    char *in_file = argv[1];
    clock_t t;
    cout << "生成归并段..." << endl;
    num_of_runs = 6;
    t = clock();
    num_of_runs = GenerateRuns(in_file);
    t = clock() - t;
    cout << "归并段生成成功， 数量:" << num_of_runs << endl;
    cout << "耗时: " << (double)t / CLOCKS_PER_SEC << "s" << endl;
    cout << "归并开始..." << endl;
    t = clock();
    for(int i = 0; i < num_of_runs; i++)
        runs[i] = new Run();
    
    //只归并了一次，一次性将所有文件归并
    MergeSort(runs, num_of_runs, "sorted");
    t = clock() - t;
    cout << "归并成功." << endl;
    cout << "耗时: " << (double)t / CLOCKS_PER_SEC << "s" << endl;
}
