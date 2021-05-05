#include<bits/stdc++.h>
#define ll long long

using namespace std;

bool comp(pair<int,pair<int,int>> pp1, pair<int,pair<int,int>> pp2){
    if(pp1.second.first == pp2.second.first){
        return (pp1.second.second < pp2.second.second);
    }
    else{
        return (pp1.second.first < pp2.second.first);
    }
}

vector<ll> buildSuffixArray(string str){
    vector<pair<int,pair<int,int>>> suffix(str.size());

    vector<ll> index(str.size());

    for(ll i=0;i<str.size();i++){
        ll frank=str[i]-'0';
        ll srank;
        if((i+1)<str.size())   srank=str[i+1]-'0';
        else srank=-1;
        suffix[i]={i,{frank,srank}};
    }

    sort(suffix.begin(), suffix.end(), comp);
	
	ll n = str.size();
    for(ll p=4;p<(n << 1);p <<= 2){
        ll rank=0;
        ll previous_rank=suffix[0].second.first;
        suffix[0].second.first=rank;
        index[suffix[0].first]=0;

        for(ll i=1;i<str.size();i++){
            if(suffix[i].second.first==previous_rank && suffix[i].second.second==suffix[i-1].second.second){
                previous_rank=suffix[i].second.first;
                suffix[i].second.first=rank;
            }
            else{
                rank++;
                previous_rank=suffix[i].second.first;
                suffix[i].second.first=rank;
            }
            index[suffix[i].first]=i;
        }
        for(ll i=0;i<str.size();i++){
            ll next_rank=suffix[i].first + p/2;
            if(next_rank<str.size()){
                suffix[i].second.second = suffix[index[next_rank]].second.first;
            }
            else{
                suffix[i].second.second = -1;
            }
        }
        sort(suffix.begin(), suffix.end(), comp);
    }

    vector<ll> suffix_vector;
    for(auto i : suffix){
    	suffix_vector.push_back(i.first);
	}
	
    return suffix_vector;
}

int main(){

    string str;
    cin>>str;

    string str2=str+str;
    vector<ll> SuffixArr=buildSuffixArray(str2);

    ll startPos=0;
    
    for(ll i=0;i<str2.size();i++){
        if(SuffixArr[i]<str.size()){
            startPos=SuffixArr[i];
            break;
        }
    }

    cout<<str2.substr(startPos,str.size())<<endl;

    return 0;
}
