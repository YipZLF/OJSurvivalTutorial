# OJ求生手册

```
#include<iostream>
#include<cstring>
#include<stack>
#include<deque>
#include<queue>
#include<map>
#include<string>
```

## STL基础

### 基本概念

* 容器 container: 存放数据的类模板
* 迭代器 iterator: 指针
  * 正向迭代器
    * ++p：指向下一个
  * 反向迭代器
    * ++p：指向上一个
  * 随机访问 
    * p[i]
    * p+=i; p-=i;
    * p+i;p-i
* 算法algorithm: 函数模板
* 顺序容器：
  * vector, deque
  * list
* 关联容器：
  * set, multiset
  * map,multimap
* 容器适配器：
  * stack,queue, priority_queue

### Notes

* 迭代：注意写++i而不是i++。 因为后者会把操作的对象复制一遍再进行+1。

* 重载比较运算符：<就够了。

  ```cpp
  bool classname::operator<(T & a, T & b){
      return a.value<b.value;
  }
  ```

* 所有区间[first,last)

### 顺序容器

#### vector

```cpp
vector(int n);
vector(int n, const T & val);//全部初始化为val
```

* 会有多余的空间。加入新元素的时候如果超出了原有的空间就要新分配一个空间然后复制过去。**增加元素几乎是，但不是常数时间。**
* 删除和插入涉及元素移动

#### list

* 双向链表。不支持随机存取元素。

#### deque

* 可以对**头元素**操作：多出push_front和pop_front
* 存取元素比vector慢

### 函数对象

* 重载了"()"这个运算符，这么这个函数就叫做函数对象类。

### 关联容器

* 排好序的4种关联容器
  * set:无重复元素
  * multiset:有重复元素
  * map:键值对，按照键排序，键没有重复
  * multimap:键值对，键可以重复

* 成员函数：

  * 111

* pair:

  ```cpp
  pair<string,int> p1("this",20);
  cout<<p1.first<<","<<p1,second<<endl;
  pair<int,string> p2 = make_pair(200,"hello");
  ```

#### multiset & set

* #include<set>
* 

## 线性表

### 0201 字符串比较简单题

* 字符串比较。
* 分为完全匹配、差一个字、少一个字
* 注意对不同情况分类讨论，讨论清楚。

### 0202 队列模拟题

* 按一定顺序发牌，需要找出胜利点的位置。

* 有一些问题可以用模拟的办法实现
* 栈or队列。可以用deque也可以用数组。

### 0203 字符串插入简单题

* 数清楚字符下标和长度的关系

### 0204 最小循环节，Next数组应用

* 前缀中的周期。KMP算法。

* 若len % (len - (next[len-1])) == 0（其中next[len-1] != 0），则T有长度为(len - (next[len-1]))的循环节（长度最小的重复单位）。

* 例如 aabaabaab, next=[-1,0,1,0,1,2,3,4,5]

* 按照教材的定义，需要把next[len]补充正确：

  ```cpp
  if(str[len-1]==str[next[len-1]])
  	next[len] = next[len-1]+1
  
  if(i%(i - (next[i]) ==0 && next[i]!=0)
     
  ```

### 0205 多项式加法-map使用范例（也可以用数组实现）

* 注意输入数据有可能会出现重复幂次，所以每次输入都要检查原来的map里面是否有与输入相同的键值

### 0206 位查询-位运算简单题

* 要加、求某位是不是1.
* 注意移位的运用：1<<1 == 2

* 没什么要注意的。。

### 0207 翻转棋盘-DFS

* 4*4的翻转棋盘，其实搜索空间就是一个{0,1}^16。翻转或不翻转。用DFS就可以了。

### 0209 找连续矩形区域内最大面积矩形-利用栈化归

* 构造一个单调递增的栈。注意分析问题，使用数据结构。
* 注意while(!st.empty() && st.top().h>=s[i].h)
  * 这里面&& 前后不能调换顺序
  * 写代码的时候还是需要谨慎一些
  * 注意细节

### 0211 Matrix 最小化 列和的最大值

* 简单搜索题：dfs

### 0213 NumberSequence-简单的计算题

* 解(k+1)k/2 = num的方程

### 0215 放苹果-递推，动态规划

* 可以对问题进行数学的分析然后再做。

### 0216 

### 0218螺旋方阵奥秘-模拟和技巧结合

* 如果模拟做不出来，应该考虑一些数学推导或者技巧的简化
* 这一题可以一层一层拨开。如果考察数字是最外层，那就用最外层的做法，如果不是，那就降阶考虑。

## 栈和队列

### 0301 滑动窗口-单调队列[经典]

* 单调队列就是队列内是单调的（例如单调递增）
  * 插入a时从后面开始看，如果rear的元素比插入元素a大，那就pop（循环下去）
* 这个问题还需要删除前面的元素，因为元素会离开滑动窗口。

## 字符串

### 0403 全在其中-简单的字符串匹配

不需要用到kmp算法

### 0404字符串乘方-kmp的next数组

找到循环的子串

## 0408 同0204

## 二叉树

### 0501 找同样先根、后根的二叉树个数

* 二叉树的题很多都需要用递归的想法
* 这里可以把问题拆分成子问题，递归求解。
* 样例：$C_{13}^3*(C_{13}^1C_{13}^2)(C_{13}^4)(1)$

### 0502 策略游戏：二分图最大匹配 匈牙利算法

```cpp
int dfs(int u){
    for(int i = 0 ; i < tree[u].size();++i){
        int v = tree[u][i];
        if(!vis[v]){
            vis[v] = true;
            if(usd[v]==-1 || dfs(usd[v])){
                usd[u] = v;
                return true;
            }
        }
    }
    return false;
}
```

### 0510重建二叉树

* 习惯使用数组指标
* 全局变量cnt使用
* 二叉树主要是递归

## 树

### 0603 发现它抓住它-并查集解决“已知”“未知”问题

* 区分已知和未知的集合，例如S1 S2 S3.. Sm是m个集合，Si内元素相互之间的关系已经知道，任何一个Si和Sj中的元素关系未知。
* 例如食物链和这一题都是一样。关系是有传递性的
* 在构造改树的时候可以把关系改了
* 并查集：维护一个父节点数组；维护一个要考察的量的数组。

## 图

### 0713 Floyd 模板题-兔子与樱花

* 想循环：
  * 需要什么量，循环如何完成
  * 如何初始化循环需要的量
  * 如何终止。
* INF 定义到0xffffff就可以了，这个可能会溢出

```pseudocode
初始化
	D[i][i] = 0;
	path[i][i] = i;
	D[i][j] = INF;
	path[i][j] = -1;
三重循环
	for k in range(num):
		for i in range(num):
			for j in range(num):
				if(D[i][k]+D[k][j]< D[i][j])
					update D[i][j]
```

### Kruskal 模板题- 兔子与星空

* 函数类型不要写错了，一定要细心。粗心意味着浪费很多时间。

* 粗心意味着浪费很多时间。

* Kruskal需要实现并查集

  ```pseudocode
  int find(int i)
  	if father[i]==i:
  		return i;
  	else return father[i]= find(father[i]);
  	
  void Merge(a,b):
  	fa = find(a);
  	fb = find(b);
  	if(fa != fb)
  		parent[fb] = fa;
  ```


### Bellman Ford / SPFA 模板题-Currency Exchange

* 最小化权值路径->最大化权值路径
* SPFA更快一点，但是实现麻烦一些。
  * 维护一个vis[V]避免重复进环，出现死循环
  * 维护一个cnt[V]记录每个节点被更改的次数，大于等于V 的时候就是有负环/正环
* 初始化、执行、判断是否正环

```pseudocode
bool SPFA(start){
    for i in range(V):
    	dist[i] = INF;
    dist[start] = 0;
    queue<int> qe;
    qe.push(start);
    vis[start] = true; //vis 表示是否在队内
    
    while(!qe.empty){
    	u = qe.top(); qe.pop();
    	vis[u] = 0;
        for e in edges;
        	if e.from == u:
        		v = e.to
        		if(dist[v] < dist[u]+e.weight)
        			dist[v] < dist[u]+e.weight
        			if vis[u] == false:
        				qe.push(u)
        				vis[u] = true
        			if(++cnt[v]>V)
        				print 有正环
    }
    print 无正环
}
```

### Prim题目 -Truck History

* 稠密图，可以用邻接矩阵实现Prim
  * 维护一个lowdis，记录目前S集合里面到V-S集合边的最小值（lowdis[i]=0表示i在S里面）

## 排序

### 归并排序模板题-归并排序求逆序数

* 提高代码可读性，不要在while循环里面加太多条件判断，背ppt上的就好了

  ```cpp
  int *array,*tmparray;
  /* Merge_sort(left,right)的作用是把[left,right]的元素排序好*/
  void Merge_sort(int left,int right)
  {
      if(right - left < 1)
          return;
      int mid = (left+right)/2;
      Merge_sort(left,mid);
      Merge_sort(mid+1,right);
      
      int pl = left, pr = mid+1, x = left;
      while(pl<=mid && pr <= right){
          if(array[pl]<array[pr]){
              tmparray[x++] = array[pl++];
          }else{
              tmparray[x++] = array[pr++];
          }
      }
      while(pl<=mid){
          tmparray[x++] = array[pl ++];
      }
      while(pr<right){
          tmparray[x++] = array[pr ++];
      }
      for(x = left;x<=right;++x){
          array[x] = tmparray[x];
      }
      
  }
  ```


* 判断逆序数的时候要注意，如果是后半边的元素比左半边的元素小
  * cnt += mid + 1 - pl;
* 要注意逆序数可能会很大，例如Ultra-quicksort 要注意**int64_t** cnt

* 

