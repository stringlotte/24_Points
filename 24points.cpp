#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <windows.h>
#include <map>
#include <stack>
#include <sstream>
#include <iostream>

using namespace std;

int NUM=4,your_score=0;
bool flag;


int str2num(string qwq)
{
	int ret=0;
	for(int i=0;i<qwq.size();i++)
	{
		ret=ret*10+qwq[i]-'0';
	}
	return ret;
}

string addnum(string qwq,double QAQ)
{
	char tmp[100];
	if(QAQ<0)
		qwq+='(';
	sprintf(tmp,"%.2lf",QAQ);
	qwq+=tmp;
	if(QAQ<0)
		qwq+=')';
	return qwq;
}

int calculate(string infix)
{
	
	string postfix[105];
	int pindex=0;
	stack<char> zhan;
	map<char,int> prio;
	prio.insert(pair<char,int>('*',2));
	prio.insert(pair<char,int>('/',2));
	prio.insert(pair<char,int>('+',1));
	prio.insert(pair<char,int>('-',1));
	prio.insert(pair<char,int>('(',0));
	for(int i=0;i<infix.size();i++)
	{
		if(infix[i]>='0' && infix[i]<='9')
		{
			postfix[pindex]+=infix[i];
		}
		else
		{
			pindex++;
			if(infix[i]=='(')
				zhan.push('(');
			else if(infix[i]==')')
			{
				while(zhan.top()!='(')
				{
					postfix[pindex++]+=zhan.top();
					zhan.pop();
				}
				zhan.pop();
			}
			else
			{
				while(!zhan.empty() && prio[zhan.top()]>=prio[infix[i]])
				{
					postfix[pindex++]+=zhan.top();
					zhan.pop();
				}
				zhan.push(infix[i]);
			}
		}
	}
	while(!zhan.empty())
	{
		postfix[++pindex]+=zhan.top();
		zhan.pop();
	}
	
	int tmp;
	stack<int>zhan2;
	for(int i=0;i<=pindex;i++)
	{
		if(postfix[i].size()==0)
			continue;
		if(postfix[i][0]>='0' && postfix[i][0]<='9')
		{
			zhan2.push(str2num(postfix[i]));
		}
		else if(postfix[i][0]=='*')
		{
			tmp=zhan2.top();
			zhan2.pop();
			tmp*=zhan2.top();
			zhan2.pop();
			zhan2.push(tmp);
		}
		else if(postfix[i][0]=='/')
		{
			tmp=zhan2.top();
			zhan2.pop();
			tmp=zhan2.top()/tmp;
			zhan2.pop();
			zhan2.push(tmp);
		}
		else if(postfix[i][0]=='+')
		{
			tmp=zhan2.top();
			zhan2.pop();
			tmp+=zhan2.top();
			zhan2.pop();
			zhan2.push(tmp);
		}
		else
		{
			tmp=-zhan2.top();
			zhan2.pop();
			tmp+=zhan2.top();
			zhan2.pop();
			zhan2.push(tmp);
		}
	}
	
	return zhan2.top();
}


int is_24(double v)
{
	double d=v-24;
	if(d<0)
		d=-d;
	if(d<0.000000001)
		return 1;
	return 0;
}

void gen_new(double numbers[],char exp_list[][20],int i,int j,double r,char *op,int count,double new_numbers[],char new_exp_list[][20])
{
	new_numbers[0]=r;
	sprintf(new_exp_list[0],"(%s%s%s)",exp_list[i],op,exp_list[j]);
	int k=1;
	for(int l=0;l<count;l++)
	{
		if(l!=i && l!=j)
		{
			new_numbers[k]=numbers[l];
			strcpy(new_exp_list[k],exp_list[l]);
			k++; 
		}
	}
}

int ans24(double numbers[],int count,char exp_list[][20])
{
	if(count==2)
	{
		double r;
		r=numbers[0]+numbers[1];
		if(is_24(r))
		{
			printf("%s+%s\n",exp_list[0],exp_list[1]);
			return (1);
		}
		r=numbers[1]-numbers[0];
		if(is_24(r))
		{
			printf("%s-%s\n",exp_list[1],exp_list[0]);
			return (1);
		}
		r=numbers[0]-numbers[1];
		if(is_24(r))
		{
			printf("%s-%s\n",exp_list[0],exp_list[1]);
			return (1);
		}
		r=numbers[1]*numbers[0];
		if(is_24(r))
		{
			printf("%s*%s\n",exp_list[1],exp_list[0]);
			return (1);
		}
		if(numbers[0]!=0)
		{
			r=numbers[1]/numbers[0];
			if(is_24(r))
			{
				printf("%s/%s\n",exp_list[1],exp_list[0]);
				return (1);
			}
		}
		if(numbers[1]!=0)
		{
			r=numbers[0]/numbers[1];
			if(is_24(r))
			{
				printf("%s/%s\n",exp_list[0],exp_list[1]);
				return (1);
			}
		}
		return (0);
	}
	else
	{
		for(int i=0;i<count-1;i++)
			for(int j=i+1;j<count;j++)
			{
				double r,new_numbers[4];
				char new_exp_list[4][20];
				r=numbers[i]+numbers[j];
				gen_new(numbers,exp_list,i,j,r,"+",count,new_numbers,new_exp_list);
				if(ans24(new_numbers,count-1,new_exp_list)==1)
					return (1);
				r=numbers[i]-numbers[j];
				gen_new(numbers,exp_list,i,j,r,"-",count,new_numbers,new_exp_list);
				if(ans24(new_numbers,count-1,new_exp_list)==1)
					return (1);	
				r=numbers[j]-numbers[i];
				gen_new(numbers,exp_list,j,i,r,"-",count,new_numbers,new_exp_list);
				if(ans24(new_numbers,count-1,new_exp_list)==1)
					return (1);	
				r=numbers[i]*numbers[j];
				gen_new(numbers,exp_list,i,j,r,"*",count,new_numbers,new_exp_list);
				if(ans24(new_numbers,count-1,new_exp_list)==1)
					return (1);	
				if(ans24(new_numbers,count-1,new_exp_list)==1)
					return (1);
				if(numbers[j]!=0)
				{
					r=numbers[i]/numbers[j];
					gen_new(numbers,exp_list,i,j,r,"/",count,new_numbers,new_exp_list);
					if(ans24(new_numbers,count-1,new_exp_list)==1)
						return (1);	
				}
				if(numbers[i]!=0)
				{
					r=numbers[j]/numbers[i];
					gen_new(numbers,exp_list,j,i,r,"/",count,new_numbers,new_exp_list);
					if(ans24(new_numbers,count-1,new_exp_list)==1)
						return (1);	
				}
			}
	}
	return (0);	
}

string hint[1000];
int hcnt;

int try24(double numbers[],int count,char exp_list[][20])
{
	if(count==2)
	{
		double r;
		r=numbers[0]+numbers[1];
		if(is_24(r))
		{
			flag=true;
			hint[0]=addnum(hint[0],numbers[0]);
			hint[0]+='+';
			hint[0]=addnum(hint[0],numbers[1]);
			return (1);
		}
		r=numbers[1]-numbers[0];
		if(is_24(r))
		{
			flag=true;
			hint[0]=addnum(hint[0],numbers[1]);
			hint[0]+='-';
			hint[0]=addnum(hint[0],numbers[0]);
			return (1);
		}
		r=numbers[0]-numbers[1];
		if(is_24(r))
		{
			flag=true;
			hint[0]=addnum(hint[0],numbers[0]);
			hint[0]+='-';
			hint[0]=addnum(hint[0],numbers[1]);
			return (1);
		}
		r=numbers[1]*numbers[0];
		if(is_24(r))
		{
			flag=true;
			hint[0]=addnum(hint[0],numbers[0]);
			hint[0]+='*';
			hint[0]=addnum(hint[0],numbers[1]);
			return (1);
		}
		if(numbers[0]!=0)
		{
			r=numbers[1]/numbers[0];
			if(is_24(r))
			{
				flag=true;
				hint[0]=addnum(hint[0],numbers[1]);
				hint[0]+='/';
				hint[0]=addnum(hint[0],numbers[0]);
				return (1);
			}
		}
		if(numbers[1]!=0)
		{
			r=numbers[0]/numbers[1];
			if(is_24(r))
			{
				flag=true;
				hint[0]=addnum(hint[0],numbers[0]);
				hint[0]+='/';
				hint[0]=addnum(hint[0],numbers[1]);
				return (1);
			}
		}
		return (0);
	}
	else
	{
		for(int i=0;i<count-1;i++)
			for(int j=i+1;j<count;j++)
			{
				double r,new_numbers[4];
				char new_exp_list[4][20];
				r=numbers[i]+numbers[j];
				gen_new(numbers,exp_list,i,j,r,"+",count,new_numbers,new_exp_list);
				if(try24(new_numbers,count-1,new_exp_list)==1)
				{
					cout<<hcnt-1<<' '<<hint[hcnt-1]<<" + "<<numbers[i]<<' '<<numbers[j]<<endl;
					hint[hcnt]=addnum(hint[hcnt],numbers[i]);;
					hint[hcnt]+='+';
					hint[hcnt]=addnum(hint[hcnt++],numbers[j]);;
					return (1);
				}
				r=numbers[i]-numbers[j];
				gen_new(numbers,exp_list,i,j,r,"-",count,new_numbers,new_exp_list);
				if(try24(new_numbers,count-1,new_exp_list)==1)
				{
					cout<<hcnt-1<<' '<<hint[hcnt-1]<<" - "<<numbers[i]<<' '<<numbers[j]<<endl;
					hint[hcnt]=addnum(hint[hcnt],numbers[i]);;
					hint[hcnt]+='-';
					hint[hcnt]=addnum(hint[hcnt++],numbers[j]);;
					return (1);	
				}
				r=numbers[j]-numbers[i];
				gen_new(numbers,exp_list,j,i,r,"-",count,new_numbers,new_exp_list);
				if(try24(new_numbers,count-1,new_exp_list)==1)
				{
					cout<<hcnt-1<<' '<<hint[hcnt-1]<<" - "<<numbers[j]<<' '<<numbers[i]<<endl;
					hint[hcnt]=addnum(hint[hcnt],numbers[j]);;
					hint[hcnt]+='-';
					hint[hcnt]=addnum(hint[hcnt++],numbers[i]);;
					return (1);	
				}
				r=numbers[i]*numbers[j];
				gen_new(numbers,exp_list,i,j,r,"*",count,new_numbers,new_exp_list);
				if(try24(new_numbers,count-1,new_exp_list)==1)
				{
					cout<<hcnt-1<<' '<<hint[hcnt-1]<<" * "<<numbers[i]<<' '<<numbers[j]<<endl;
					hint[hcnt]=addnum(hint[hcnt],numbers[i]);;
					hint[hcnt]+='*';
					hint[hcnt]=addnum(hint[hcnt++],numbers[j]);;
					return (1);	
				}
				if(numbers[j]!=0)
				{
					r=numbers[i]/numbers[j];
					gen_new(numbers,exp_list,i,j,r,"/",count,new_numbers,new_exp_list);
					if(try24(new_numbers,count-1,new_exp_list)==1)
					{
						cout<<hcnt-1<<' '<<hint[hcnt-1]<<" / "<<numbers[i]<<' '<<numbers[j]<<endl;
						hint[hcnt]=addnum(hint[hcnt],numbers[i]);;
						hint[hcnt]+='/';
						hint[hcnt]=addnum(hint[hcnt++],numbers[j]);;
						return (1);	
					}
				}
				if(numbers[i]!=0)
				{
					r=numbers[j]/numbers[i];
					gen_new(numbers,exp_list,j,i,r,"/",count,new_numbers,new_exp_list);
					if(try24(new_numbers,count-1,new_exp_list)==1)
					{
						cout<<hcnt-1<<' '<<hint[hcnt-1]<<" / "<<numbers[j]<<' '<<numbers[i]<<endl;
						hint[hcnt]=addnum(hint[hcnt],numbers[j]);;
						hint[hcnt]+='/';
						hint[hcnt]=addnum(hint[hcnt++],numbers[i]);;
						return (1);	
					}
				}
			}
	}
	return (0);	
}

int main()
{
	double numbers[NUM];
	char exp_list[NUM][20],hehe[3];
	printf("Welcome to 24-points-English!\n");
	Sleep(100);
	printf("We will give you a solvable 24-points question. ");
	printf("You will get 3 points if you solve one without hint(and 2 for one hint, 1 for 2 hints).\n");
	Sleep(100);
	printf("You can solve it by +,-,* and /.\n");
	Sleep(100);
	printf("Remember, '*' cannot be omitted!\n\n");
	Sleep(100);
	printf("Settings: \n");
	Sleep(100);
	printf("How many cards do you want to have?(Not less than 4 or greater than 20)\nInput an integer: ");
	cin>>NUM;
	NUM=max(NUM,4);
	srand((unsigned)time(NULL));
	while(1)
	{
		
		hcnt=1;
		hint[0]=hint[1]=hint[2]="";
		flag=false;
		for(int z=0;z<NUM;z++)
		{
			numbers[z]=rand()%14;
			while(numbers[z]==0)
				numbers[z]=rand()%14;
		}	
		for(int i=0;i<NUM;i++)
		{
			sprintf(exp_list[i],"%d",int(numbers[i]));
		}
		try24(numbers,NUM,exp_list);
		if(!flag)
		{
			continue;
		}
		for(int i=0;i<hcnt;++i)
		{
			cout<<hint[i]<<endl;
		}
		for(int i=0;i<NUM;i++)
		{
			printf("%d ",int(numbers[i]));
		}
		printf("\n");
		
		printf("Input your answer (NO SPACE) : ");
		string ANS;
		cin>>ANS;
		
		if(calculate(ANS)==24)
		{
			bool flagg=true;
			int SNUM[14],RNUM[14];
			for(int i=0;i<14;i++)
				SNUM[i]=0,RNUM[i]=0;
			for(int i=0;i<NUM;i++)
				SNUM[int(numbers[i])]++;
			int curnum=0;
			for(int i=0;i<ANS.size();i++)
			{
				if(ANS[i]>='0' && ANS[i]<='9')
					curnum=curnum*10+ANS[i]-'0';
				else
					RNUM[curnum]++,curnum=0;
			}
			RNUM[curnum]++;
			for(int i=1;i<14;i++)
			{
				if(SNUM[i]!=RNUM[i])
				{
					cout<<i<<' '<<SNUM[i]<<' '<<RNUM[i]<<endl;
					goto WA;
				}
			}
			your_score+=3;
			cout<<"Correct!\n";
			
		}
		else
		{
WA:			cout<<"Wrong Answer!\n";
			printf("Input one character to see one of the correct answers\n");
			char temp;
			cin>>temp;
			ans24(numbers,NUM,exp_list);
		}
		while(1)
		{
			printf("Input [1] to exit, [2] to continue, [3] to see your score, [4] to change the setting\n");
			cin>>hehe;
			if(hehe[1]=='1')
			{
				cout<<"See you~\n";
				Sleep(100);
				printf("By @no_proper_name_left\n");
				return 0;
			}
			if(hehe[1]=='2')
			{
				cout<<endl;
				break;
			}
			if(hehe[1]=='3')
			{
				cout<<your_score<<endl;
			}
			if(hehe[1]=='4')
			{
				printf("Settings: \n");
				Sleep(100);
				printf("How many cards do you want to have?(Not less than four)\nInput an integer: ");
				cin>>NUM;
				NUM=max(NUM,4);
			}
		}
	}
	return 0;
}
