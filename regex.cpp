#include<iostream>
#include<string>

using namespace std;
int match_here(string,string);

int match_star(char c,string regex,string text)
{
    do{
        if(match_here(regex,text))
            return 1;
        text.erase(0,1);
    }  while(!text.empty() && (text[0]==c || c=='.'));
    //as now text[0]!=c
    if (match_here(regex,text))
        return 1;
    
    return 0;
}
int match_plus(char c,string regex,string text)
{
    char x=c;
    if (text[0]==x)
        return match_star(x,regex,text);
    return 0;
}
int match_or(char c,string regex,string text)
{
    if(text[0]==c || c=='.') 
       return match_here(regex,text.erase(0,1));
    else
        return match_here(regex,text);
}

int match_here(string regex,string text)
{
    char x;
    if (regex.empty())
        return 1;
    //do *,?,$,,+
    //$
    if(regex[0]=='$' && regex.size()==1)
        return text.empty();
    //*
    if (regex.size()>=2 && regex[1]=='*')
    {
        x=regex[0];
        return match_star(x,regex.erase(0,2),text);
    }
    //+
    if (regex.size()>=2 && regex[1]=='+')
    {
        x=regex[0];
        return match_plus(x,regex.erase(0,2),text);
    }
    //?
    if (regex.size()>=2 && regex[1]=='?')
    {
        x=regex[0];
        return match_or(x,regex.erase(0,2),text);
    }
    if(!text.empty() && (regex[0]=='.' || regex[0]==text[0]))
        return match_here(regex.erase(0,1),text.erase(0,1));
    return 0;
}

int match(string regex,string text)
{
    if(regex[0]=='^')
        return match_here(regex.erase(0,1),text);
    do{
        if(match_here(regex,text))
            return 1;
        text.erase(0,1);
    }while(!text.empty());
    return 0;
}

int main()
{
    string a,b;
    cin>>a>>b;
    cout<<match(a,b);

    return 0;
}