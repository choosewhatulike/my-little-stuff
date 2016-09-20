#include<iostream>
#include<vector>

using namespace std;
//计算一个关系有多少传递子关系的小程序
class Item {
  public:
    int a, b;
    Item(int _a=0, int _b=0) {
        a = _a;
        b = _b;
    }

};

class Relation {
  public:
    vector<Item> re;
    Relation(){}
    Relation(vector<int>& a) {
        for(int i=0; i<a.size(); ++i) {
            for(int j=0; j<a.size(); ++j) {
                Item it(a[i], a[j]);
                re.push_back(it);
            }
        }
    }

    bool isChuandi();
    int ChuandiSetNum();
    int find_a(int _a) {
        for(int i=0; i<re.size(); ++i) {
            if(re[i].a == _a)
                return i;
        }
        return -1;
    }
    int find_b(int _b) {
        for(int i=0; i<re.size(); ++i) {
            if(re[i].b == _b)
                return i;
        }
        return -1;
    }
    int find_ab(int _a, int _b) {
        for(int i=0; i<re.size(); ++i) {
            if(re[i].a == _a && re[i].b == _b)
                return i;
        }
        return -1;
    }
    void printRe(){
        for(int i=0;i<re.size();++i){
            cout <<'('<< re[i].a <<','<<re[i].b<<')'<<' ';
        }
        cout<<endl;
    }

};
//检验是否传递
bool Relation::isChuandi(){
    int index;
    for(int i=0; i<re.size(); ++i) {
        if((index = find_a(re[i].b)) != -1) {
            if(find_ab(re[i].a, re[index].b) == -1)
                return false;
        }
    }
    return true;
}

//生成排列组合数,无序
bool MakeC(int *r, int index, int n, int jin) {
    r[index] += jin;
    if(r[index] > n) {
        if(index == 0) {
            return false;
        }
        MakeC(r, index - 1, n-1, 1);
        r[index] = r[index - 1] + 1;
        if(r[index] > n)
            return false;
    }
    if(r[0] == 0)
        MakeC(r, index, n, 1);

    return true;
}
//找出传递子关系的个数
int Relation::ChuandiSetNum() {
    int amou;
    int cou = 0;
    int cr, mul_amou;
    int i = 0;
    for(amou = 1; amou <= re.size(); ++amou) {
        //计算从n个元素中去r个元素有多少取法cr
        for(i = 0, mul_amou = 1, cr = 1; i<amou; ++i) {
            cr *= re.size() - i;
            mul_amou *= i+1 ;
        }
        cr /= mul_amou;

        //初始化下标集r
        int *r = new int[amou];
        for(int i=0;i<amou;++i){
            r[i] = i;
        }
        while(MakeC(r, amou - 1, re.size(), 1)) {
            //生成子集
            Relation tempset;
            for(int i=0; i<amou; ++i) {
                //cout<<r[i]<<' ';
                tempset.re.push_back(re[r[i]-1]);
            }
            //判断是否传递and计数
            if(tempset.isChuandi()){
                cou++;
                //tempset.printRe();
            }
        }

    }
    return cou;
}

int main() {
    vector<int> a;
    for(int i=0;i<3;++i){
        a.push_back(i+1);
    }
    Relation re(a);
    re.printRe();
    cout << re.ChuandiSetNum() << endl;
}
