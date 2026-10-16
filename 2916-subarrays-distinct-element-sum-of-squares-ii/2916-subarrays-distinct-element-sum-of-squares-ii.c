int cmp(const void*a,const void*b){return (*(int*)a - *(int*)b);}
#define MOD 1000000007LL
#define MAXN 100005
long long sumT[4*MAXN], sumSqT[4*MAXN], lazy[4*MAXN];

void apply(int node,int l,int r,long long v){
    long long len=r-l+1;
    sumSqT[node]=(sumSqT[node]+2*v*sumT[node]+v*v%MOD*len)%MOD;
    sumT[node]=(sumT[node]+v*len)%MOD;
    lazy[node]=(lazy[node]+v)%MOD;
}
void push(int node,int l,int r){
    if(lazy[node]!=0 && l!=r){
        int mid=(l+r)/2;
        apply(node*2,l,mid,lazy[node]);
        apply(node*2+1,mid+1,r,lazy[node]);
    }
    lazy[node]=0;
}
void rangeAdd(int node,int l,int r,int ql,int qr,long long v){
    if(ql>r||qr<l) return;
    if(ql<=l && r<=qr){apply(node,l,r,v);return;}
    push(node,l,r);
    int mid=(l+r)/2;
    rangeAdd(node*2,l,mid,ql,qr,v);
    rangeAdd(node*2+1,mid+1,r,ql,qr,v);
    sumT[node]=(sumT[node*2]+sumT[node*2+1])%MOD;
    sumSqT[node]=(sumSqT[node*2]+sumSqT[node*2+1])%MOD;
}
void pointSet(int node,int l,int r,int idx){
    if(l==r){sumT[node]=1;sumSqT[node]=1;lazy[node]=0;return;}
    push(node,l,r);
    int mid=(l+r)/2;
    if(idx<=mid) pointSet(node*2,l,mid,idx);
    else pointSet(node*2+1,mid+1,r,idx);
    sumT[node]=(sumT[node*2]+sumT[node*2+1])%MOD;
    sumSqT[node]=(sumSqT[node*2]+sumSqT[node*2+1])%MOD;
}

int sumCounts(int* nums, int numsSize){
    int n=numsSize;
    int *tmp=malloc(n*sizeof(int));
    memcpy(tmp,nums,n*sizeof(int));
    qsort(tmp,n,sizeof(int),cmp);
    int m=0;
    int *uniq=malloc(n*sizeof(int));
    for(int i=0;i<n;i++) if(i==0||tmp[i]!=tmp[i-1]) uniq[m++]=tmp[i];
    int *last=calloc(m,sizeof(int));
    memset(sumT,0,sizeof(sumT));
    memset(sumSqT,0,sizeof(sumSqT));
    memset(lazy,0,sizeof(lazy));
    long long ans=0;
    for(int r=1;r<=n;r++){
        int v=nums[r-1], lo=0, hi=m-1, id=-1;
        while(lo<=hi){int mid=(lo+hi)/2; if(uniq[mid]==v){id=mid;break;} if(uniq[mid]<v) lo=mid+1; else hi=mid-1;}
        int prev=last[id];
        if(prev==0){ if(r>1) rangeAdd(1,1,n,1,r-1,1); }
        else{ if(prev+1<=r-1) rangeAdd(1,1,n,prev+1,r-1,1); }
        pointSet(1,1,n,r);
        last[id]=r;
        ans=(ans+sumSqT[1])%MOD;
    }
    free(tmp);free(uniq);free(last);
    return (int)ans;
}