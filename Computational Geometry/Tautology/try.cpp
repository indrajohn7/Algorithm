#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<bits/stdc++.h>
#include<list>
#include<string.h>

using namespace std;

#define X '0'
#define Y '1'
#define N  100000


        list<char> Stream;

int  main(int argc,char* input1[])
{
	//Write code here
	 char Sol[200];
        int i=0,j=0,T;
      strcpy(Sol,input1[1]);
        while(Sol[i]!='\0')
        {
                if(!(Sol[i]=='N' || Sol[i]=='O' || Sol[i]=='A' || Sol[i]=='I' || Sol[i]=='F'))
                        Sol[i]='0';
                i++;
        }
        cout<<Sol<<"\t"<<strlen(Sol)<<endl;
        char op1,op2,oper;
        op1=op2=oper='3';
        i=0,j=0;
        char Final[20];
        for(i=0;i<strlen(Sol);i++)
        {

                if(Sol[i]=='N' || Sol[i]=='A' || Sol[i]=='O' || Sol[i]=='I' ||Sol[i]=='F')
                {
                        Stream.push_front(Sol[i]);
                }
                else
                {
                        if(Sol[i+1]==X || Sol[i+1]==Y)
                        {
                                if(Stream.front()=='N')
                                {
                                        Stream.pop_front();
                                        (Sol[i]==X)?Sol[i]=Y:Sol[i]=X;
                                }
                                                                op1=Sol[i+1];
                                                                op2=Sol[i];
        if(op2=='2' && (Stream.front()!=X && Stream.front()!=Y))
        {
                if(Stream.front()=='N')
                {
                        Stream.pop_front();
                        (op1==X)?Stream.push_front('1'):Stream.push_front('0');
                }
                else
                Stream.push_front(op1);
                cout<<"Inside if:"<<"\n";
        }
        else
        {
                cout<<"Inside else calc"<< "\n";
                if(op2=='2' && (Stream.front()==X || Stream.front()==Y))
                {
                        op2=Stream.front();
                        Stream.pop_front();
                }
                oper=Stream.front();
                Stream.pop_front();
                if(oper=='N')
                {
                        (op2==X)?op2=Y:op2=X;
                        Stream.push_front(op2);
                        Stream.push_front(op1);
                }
                else if(oper=='I')
                {
                        (op2=='1' && op1=='0')?Stream.push_front('0'):Stream.push_front('1');
                }
                else if(oper=='A')
                        (op2=='1' && op1=='1')?Stream.push_front('1'):Stream.push_front('0');
                else if(oper=='O')
                        (op2=='0' && op1=='0')?Stream.push_front('0'):Stream.push_front('1');
                else if(oper == 'F')
                        (op1==op2)?Stream.push_front('1'):Stream.push_front('0');
		else
		{
			cout<<"Invalid\n";
			return 0;
		}
        }
                             //   calculate(&Stream,Sol[i+1],Sol[i]);
                                i=i+1;
                        }
                        else
                        {
                                if(Stream.front()=='N')
                                {
                                        (Sol[i]==X)?Sol[i]=Y:Sol[i]=X;
                                        Stream.pop_front();
                                }
                                                        op1=Sol[i];
                                                        op2='2';
        if(op2=='2' && (Stream.front()!=X && Stream.front()!=Y))
        {
                if(Stream.front()=='N')
                {
                        Stream.pop_front();
                        (op1==X)?Stream.push_front('1'):Stream.push_front('0');
                }
                else
                        Stream.push_front(op1);
                cout<<"Inside if:"<<"\n";
        }
        else
        {
                cout<<"Inside else calc"<< "\n";
                if(op2=='2' && (Stream.front()==X || Stream.front()==Y))
                {
                        op2=Stream.front();
                        Stream.pop_front();
                }
                oper=Stream.front();
                Stream.pop_front();
                if(oper=='N')
                {
                        (op2==X)?op2=Y:op2=X;
                        Stream.push_front(op2);
                        Stream.push_front(op1);
                }
                else if(oper=='I')
                {
                        (op2=='1' && op1=='0')?Stream.push_front('0'):Stream.push_front('1');
                }
                else if(oper=='A')
                        (op2=='1' && op1=='1')?Stream.push_front('1'):Stream.push_front('0');
                else if(oper=='O')
                        (op2=='0' && op1=='0')?Stream.push_front('0'):Stream.push_front('1');
                else if(oper == 'F')
                        (op1==op2)?Stream.push_front('1'):Stream.push_front('0');
		else
		{
			cout<<"Invalid\n";
			return 0;
		}
        }
                                                        //   calculate(&Stream,Sol[i],'2');
                        }
                }
        }
		int iter=0;
        while(Stream.size()>1)
        {
              if(iter>N)
			  {
				  strcpy(Final,"Invalid");
				  cout<<Final<<"\n";
				  return 0;
			  }				  
		op1=Stream.front();
                Stream.pop_front();
                                op2='2';
        if(Stream.front()!=X && Stream.front()!=Y)
        {
                if(Stream.front()=='N')
                {
                        Stream.pop_front();
                        (op1==X)?Stream.push_front('1'):Stream.push_front('0');
                }
                else
                        Stream.push_front(op1);
                cout<<"Inside if:"<<"\n";
        }
        else
        {
                cout<<"Inside else calc"<< "\n";
                if(op2=='2' && (Stream.front()==X || Stream.front()==Y))
                {
                        op2=Stream.front();
                        Stream.pop_front();
                }
                oper=Stream.front();
                Stream.pop_front();
                if(oper=='N')
                {
                        (op2==X)?op2=Y:op2=X;
                        Stream.push_front(op2);
                        Stream.push_front(op1);
                }
                else if(oper=='I')
                {
                        (op2=='1' && op1=='0')?Stream.push_front('0'):Stream.push_front('1');
                }
                else if(oper=='A')
                        (op2=='1' && op1=='1')?Stream.push_front('1'):Stream.push_front('0');
                else if(oper=='O')
                        (op2=='0' && op1=='0')?Stream.push_front('0'):Stream.push_front('1');
                else if(oper == 'F')
                        (op1==op2)?Stream.push_front('1'):Stream.push_front('0');
		else
		{
			cout<<"Invalid\n";
			return 0;
		}

        }
               // calculate(&Stream,x,'2');
        }
        if(Stream.front()=='1')
                strcpy(Final,"yes");
        else
                strcpy(Final,"NO");
        cout<< Final;

	return 0;
	
	
}

