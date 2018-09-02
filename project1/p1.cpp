#include<iostream>
#include<cstdio>
#include<cstdlib>

using namespace std;

char text_word[99][99]={{0}};

int main()
{		
	char word;
	int i=0;
	int j=0;
	char input_file[100000];
	char output[100000];
	//讀入檔案 
	FILE *File;
	cin>>input_file>>output;
    File = fopen(input_file, "r");
    if (File==NULL) perror ("Error opening file");
	while(1)
	{
    	word = fgetc(File);
		if(word== EOF)
		{
	 		break;
		} 
		if(word==' ' || word=='\n')
		{
			i++;
			j=0;
		}
		else
		{
			text_word[i][j]=word;
			j++;
			
		}
				
    }
    
   	
   	/*判斷關鍵字有幾個字母*/ 
   	int pattern_size=0;
   	for(int x=0;x<i+1;x++)
   	{
   	
   		if(text_word[0][x]<'a' || text_word[0][x]>'z')
   		{
   			break;	
		}
		pattern_size++;
	}
   	int pattern_appear=0;
   	/*判斷陣列*/
	for(int x=0;x<i+1;x++)
	{
		for(int y=0;y<pattern_size;y++)
		{
			if(text_word[x][y]!=text_word[0][y])
			{
				
				break;
			}
			if(y==pattern_size-1 && text_word[x][y+1]<'a' || text_word[x][y+1]>'z')
			{
				pattern_appear++;
			}
		}	
	
	}    
  
    
    /*判斷子陣列*/
    int m=0;
    int pattern_frequency[100000]={0};
	for(int x=0;x<i+1;x++)
	{
		for(int y=0;;y++)
		{
			if( text_word[x][y]<'a' || text_word[x][y]>'z')
			{
				break;	
			}				
			if(text_word[x][y]==text_word[0][0])
			{
				
				int k;
				k=y+1;
				for(int z=1;z<pattern_size;z++)
				{	
					
					if(text_word[x][k]!=text_word[0][z]){break;
					}
					if(z==pattern_size-1)
					{
						pattern_frequency[m]=x+1;
						m++;
					}
					k++;
				}	
			}
		}	
}
fclose(File);//先關閉檔案 
//寫入檔案 
File = fopen(output,"w");
fprintf(File,"%d",pattern_appear);
fprintf(File,"%c",'\n');
for(int x=0;x<m;x++)
{
	fprintf(File,"%d",pattern_frequency[x]);	
}
fclose(File);

return 0;
}
