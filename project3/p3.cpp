#include <iostream>
#include <fstream>
#include<cstring>
#include<cctype>
#include<cstdio>
#include <algorithm>
#include <queue>
using namespace std;

class edge{//declare parameter
public:
    int p1=-1,p2=-1;
    int weight=-1;
    bool readable=true;
};

int loadsort(edge* ver){//read edger
    fstream file;//read txt
    int j=-1,x=1;
    char temp[100]{};
    edge str[100];
    string open;
    cin>>open;
    file.open(open,ios::in);
    file.getline(temp, '/n');//use getline to read whole line
    while (x) {
        j++;
        int tempint=0;
        bool save=false;
        int cnt;
        cnt = 0;
        for (int i=0; i < file.gcount(); i++) {
            if (temp[i]=='\0') break;
            if (isdigit(temp[i])) {
                save=true;
                tempint*=10;
                tempint+=temp[i]-'0';
            }
            else{
                if (save) {
                    switch (cnt) {
                        case 0:
                            str[j].p1=tempint;
                            break;
                        case 1:
                            str[j].p2=tempint;
                            break;
                        default:
                            break;
                    }
                    cnt++;
                }
                save=false;
                tempint=0;
            }
        }
        str[j].weight=tempint;
        file.getline(temp, '/n');
        if (file.eof()) {
            x--;
        }
    }
    int y[j+1];
    for (int k=0;k<=j; k++) {
        y[k]=str[k].weight;
    }
    sort(y,y+j+1);//sort input data
    int index=-1;
    for (int i=0; i<=j; i++) {
        for (int k=0; k<=j; k++) {
            if (y[i]==str[k].weight) {
                ver[++index].weight=str[k].weight;
                ver[index].p1=str[k].p1;
                ver[index].p2=str[k].p2;
            }
        }
    }
    return j;
}
//check find
bool iffind(string tar, int x){
    return !(tar.find(char(x+'0'))==string::npos);//find x是否在tar裡

}

void reversestr(string& tar){
    size_t len=tar.size();
    for (int i=0; i<len/2; i++) {
        char temp=tar[i];
        tar[i]=tar[len-1-i];
        tar[len-1-i]=temp;
    }
}

string kruskal(edge* edg,int l){//do kruskal
    //declare
    string rec[10];
    bool founda=false,foundb=false;
    int ia=-1,ib=-1,index=-1;
    for (int i=0; i<10; i++) {
        rec[i]="";
    }
    for (int i=0; i<l; i++) {
        founda=false,foundb=false;
        for (int j=0; j<l; j++) {                  //detect cycle
            if (iffind(rec[j], edg[i].p1)&&iffind(rec[j], edg[i].p2)) {
                ia=ib=j; founda=foundb=true; break;//if a b 都在tar will cause cycle
            }
            else if (iffind(rec[j], edg[i].p1)&&!iffind(rec[j], edg[i].p2)){
                ia=j; founda=true;                 //only a in tar
            }
            else if (!iffind(rec[j], edg[i].p1)&&iffind(rec[j], edg[i].p2)){
                ib=j; foundb=true;                //only b in tar
            }
        }
        if (!founda&&!foundb) {                   //put p1,p2 in rec
            rec[++index]+=char(edg[i].p1+'0');
            rec[index]+=char(edg[i].p2+'0');
        }
        else if (founda&&!foundb){                //only a find
            rec[ia]=char(edg[i].p2+'0')+rec[ia];  //if a find ,put a into rec[ia]
        }
        else if (!founda&&foundb){
            rec[ib]=char(edg[i].p1+'0')+rec[ib];
        }
        else{
            if (ia==ib) {//p1,p2為同一點 but spanning tree does not allow this situation happen
                edg[i].readable=false;
                continue;
            }
            else {
                rec[ib]+=rec[ia];                //把ia ib connect
                rec[ia].clear();                 //每連完就要clear
            }
        }
    }
}

int main(){
    //declare
    edge edg[100];
    int total=0;
    int l=loadsort(edg);
    l++;
    string ans=kruskal(edg, l);
    for (int k=0;k<l; k++) {
        if (edg[k].readable)//把最後可以readable的edges 印出
        cout<<edg[k].p1<<" "<<edg[k].p2<<" "<<edg[k].weight<<endl;
    }
    for (int k=0;k<l; k++) {
        if (edg[k].readable) total+=edg[k].weight;
    }
    cout<<total<<endl;
    system("pause");
}

