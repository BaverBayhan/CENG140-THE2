#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
char *place;
void compactify_string(char* s)
{
    int i,m,last_was_blank;
    for(i=0,last_was_blank=0,m=0;s[i];i++)
    {
        if(s[i]==' ')
        {
            if(last_was_blank) continue;
            else last_was_blank=1;
        }
        else
        {
            last_was_blank=0;
            s[m]=s[i];
            m++;
        }
    }
    s[m]=0;
}
int truth_value_evaluator()
{
    int left ,right;char op;
    if(*place=='(')
    {
        place++;
        left=truth_value_evaluator();
        op=*place++;
        right=truth_value_evaluator();
        place++;
        switch (op)
        {
            case '&':
                return (left&&right);
            case '|':
                return (left||right);
            case '>':
                if(left==1 && right==1) return 1;
                else if(left==0 && right==1) return 1;
                else if(left==1 && right==0) return 0;
                else if(left==0 && right==0) return 1;
            case '=':
                return (left==right) ;
        }
    }
    else if(*place !='-')
    {
        
        sscanf(place,"%d",&left);
        while(isdigit(*place))place++;
        return left;
    }
    else if(*place =='-')
    {
        place++;
        left=truth_value_evaluator();
        if(left==1) left=0;
        else left=1;
        return left;
    }
}
int eval_helper(char *s)
{
    place=s;
    return truth_value_evaluator();
}
void unique_maker(char *str)
{
    int i,j;
    for(i=0;str[i];i++)
    {
        for(j=0;str[j];j++)
        {
            if(str[i]==str[j] && i != j)
            str[j]=' ';
        }
    }
}
void bubbleSort(char* str)
{
    int i,j,len=strlen(str);
    char temp;
    for (i = 0; i < len - 1; ++i) 
    {
        for (j = 0; j < len - i - 1; ++j)
        {
            if (str[j] > str[j + 1])
            {
                temp = str[j];
                str[j] = str[j + 1];
                str[j + 1] = temp;
            }
        }
    }
}
char* list_transformer(char* p)
{
    int temp_ascii,counter=0,i,k,new_length=0;
    char* result_pointer,*copy;
    copy=p;
    for(;*p;p++)
    {
        temp_ascii=*p;
        if(temp_ascii>=97 && temp_ascii<=122)
        {
            counter++;
        }
    }
    p=copy;
    result_pointer=malloc((counter+1)*sizeof(char));
    for(i=0,k=0;p[i];i++)
    {
        temp_ascii=p[i];
        if(temp_ascii>=97 && temp_ascii<=122 && k!=counter)
        {
            result_pointer[k]=p[i];
            k++;
        }
        if(k==counter) result_pointer[k]='\0';
    }
    unique_maker(result_pointer);
    for(i=0;result_pointer[i];i++)
    {
        if(result_pointer[i] != ' ')new_length++;
    }
    compactify_string(result_pointer);
    bubbleSort(result_pointer);
    return result_pointer;
}
int pow_of_two(int k)
{
    int result=1;
    for(;k>0;k--) result*=2;
    return result;
}
int in(char letter,char* checker_list)
{
    int lst_checker=strlen(checker_list),result=0,i;
    for(i=0;i<lst_checker;i++)
    {
        if(checker_list[i]==letter) result=1;
    }
    return result;
}
int find_index(char letter,char* transformed_lst)
{
    int index,len_transformed=strlen(transformed_lst),i;
    for(i=0;i<len_transformed;i++)
    {
        if(transformed_lst[i]==letter)
        {
            index=i;
            break;
        }
    }
    return index;
}
char eval_R(char *row_str,char* transformed_lst,char* truth_values)
{
    char* copy_of_row_str;
    int i,len_row_str=strlen(row_str),temp_index;
    char result;
    copy_of_row_str=malloc((len_row_str+1)*sizeof(char));
    for(i=0;i<=len_row_str;i++)
    {
        copy_of_row_str[i]=row_str[i];
    }
    for(i=0;i<len_row_str;i++)
    {
        if(in(copy_of_row_str[i], transformed_lst)) 
        {
            temp_index=find_index(copy_of_row_str[i],transformed_lst);
            copy_of_row_str[i]=truth_values[temp_index];
        }
    }
    if(eval_helper(copy_of_row_str)==1) result='1';
    else if(eval_helper(copy_of_row_str)==0) result='0';
    free(copy_of_row_str);
    return result;
}
void truth_table_maker(char* str_transformed,char* str_row)
{
    char put,printing_value;
    int len_str=strlen(str_transformed),i,j,expanded_length=pow_of_two(len_str-1),len_for_truth_table=strlen(str_transformed)-1,checker;
    char** result_pointer;
/************************* memory allocation ************************/
    result_pointer=malloc(expanded_length*sizeof(char *));
    for(i=0;i<expanded_length;i++)
    {
        result_pointer[i]=malloc((len_str)*sizeof(char));
    }
/************************** create truth table ***********************/
    checker=expanded_length;
    for(i=0;i<len_for_truth_table;i++)
    {
        put='1';
        checker=checker/2;

        for(j=0;j<expanded_length;j++)
        {
            if(j%checker==0 && j !=0)
            {
                if(put =='0')put='1';
                else if(put =='1')put='0';
            }
            result_pointer[j][i]=put;
        }
    }
/************************** eval R value ********************************/
    for(i=0;i<expanded_length;i++)
    {
        result_pointer[i][len_for_truth_table]= eval_R(str_row,str_transformed,result_pointer[i]);
        result_pointer[i][len_str]='\0';
    }
/************************* print result ********************************/
    for(i=0;i<expanded_length;i++)
    {
        for(j=0;j<len_str;j++)
        {
            if(result_pointer[i][j]=='1') printing_value='T';
            else if(result_pointer[i][j]=='0') printing_value='F';
            if(j==len_str-1)
            {
                
                printf("%c\n",printing_value);
            }
            else
            {
                printf("%c ",printing_value);
            }
        }
    }
}
void first_line_printer(char *a)
{
    int len_str=strlen(a),i;
    for(i=0;i<len_str;i++)
    {
        if(i==len_str-1) printf("%c\n",a[i]);
        else printf("%c ",a[i]);
    }

}
void add_R_to_str(char *str)
{
    int strlen1=strlen(str)+1;
    str=realloc(str,(strlen1+1)*sizeof(char));
    str[strlen1-1]='R';
    str[strlen1]='\0';
}

int main()
{
    int ch, i = 1;  
    char* main_str=malloc(sizeof(char));  
    char* a; 
    while((ch=getchar())!=EOF)
    {
        if(ch != '\n')
        {
            main_str=realloc(main_str,i*sizeof(char));
            main_str[i-1] = ch;  
            i++;   
        }
    }
    main_str=realloc(main_str,i*sizeof(char));
    main_str[i-1]='\0';
    compactify_string(main_str);
    a=list_transformer(main_str);
    add_R_to_str(a);
    first_line_printer(a);
    truth_table_maker(a,main_str);

    return 0;
}
