* [OpenJudege 1002 正方形](http://dsa.openjudge.cn/retrieval/1002/)

  * 哈希的一个模板题

  * 确定**要存的对象**是什么：例如点、方形等等，可以是一些结构体

  * 确定**哈希表里面**存的东西是什么：要存的对象的指针或者node数组下标

  * 实现哈希函数，开散列解决哈希冲突

    * 常用的质数：10007,1000003...

    ```cpp
    struct node{
        int a,b,..;
        int next;
    }Node[MAXN];
    
    void initHash(){
        memset(hashtable,0xff,sizeof(hashtable));
        cur = 0; 
    	Init();
    }
    
    int hash(node & p){
        ...
            return key;
    }
    
    bool insertHash(node * p){
        int key= hash(p);
        if(exist(key))
            	return false;
        else{
            Node[cur]=p;
            Node[cur].next = hashtable[key];
            hashtable[key] = cur;
            cur++;
            return true;
        }
    }
    
    bool searchHash(node & p){
        int key = hash(p);
        int next = hashtable[key];
        while(next!=-1){
            if(Node[next] == p)
                	return true;
            next = hashtable[key].next;
        }
        return false;
    }
    ```
