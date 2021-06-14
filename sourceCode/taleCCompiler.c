#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//������itoa������������ÿ��������tag������
//ע�⣬���ɳ����������˶���������math.h �� time.h
//���Ҫ���Ӷ���Ĵ���⣬���Դ�����±���һ�ݱ�����

void preprocessing(char original_text[][1023]);
void delete_blank(char* str);
unsigned long readLine(char* src[], char* dst[], char* debug_log, char* tag_log[]);
char* delete_end_blank(char*, char*);
int count_bracket(char* readed);

//unsigned long �Ѿ����ڼ������������Ĵ洢���ˣ���ȫ�㹻
//������ǧ���ı����Ĵ󹤳̣���ƽ��һ�е�������Զ��10���������Ҫ����һ�������е�����

//��˰����������������Ŀǰ�зֳ�ָ�����鲢�ҷ���ģ�黯������ʺ���һ����ʮ���ı�����С����
//�����Ը�����ˮ��ʽ��ƣ����ж�ȡ�ı�Ȼ��д���ı���


//��ȡһ�еĺ�������ȡ�󷵻ض����������
//����������û��������˵������ʧ�ܣ��������bug����Ӧ�����������debug_log�е���Ϣ

//��ȡ.tc�ļ���д����ά���飬ת��Ϊcharָ�����鴫��readline��
//��������readlineֱ���ָ�����飬��output��ָ������д��.c�ļ���

#define MAX_CODE_LINE 1023
char original_text[MAX_CODE_LINE][1023] = { 0 };
char out[MAX_CODE_LINE][1023] = { 0 };
char* text_ptr[MAX_CODE_LINE];
char* out_ptr[MAX_CODE_LINE];
int realline;

static unsigned long writeLine = 0;

int main(void) {
    char debug[1023] = { 0 };
    int __load = 0;//�ж�����Ƿ�Ҫ����
    int lastTag = 0;

    //���ļ��ж�ȡlastTag
    printf("this program is made by Shina-Mashiro.");
    printf("Are you sure to compile the source code?[y/n]\n");
    char input = getchar();
    //if (input == 'n') {
    //    __load = 0;
    //    lastTag = 0;
    //}
    //else {
    //    __load = 1;
    //}

    preprocessing(original_text);
    FILE* FileC = fopen("output.c", "w+");  //����output.c 
    if (FileC == NULL) {
        puts("Can not set up output.c!\n");
        exit(1);
    }
    //������output.c���󣬷���Can not set up output.c!

    int i;
    for (i = 0; i < MAX_CODE_LINE; i++) {
        text_ptr[i] = original_text[i];
        out_ptr[i] = out[i];
        //        puts(text_ptr[i]);
        //        printf("%d", strlen(text_ptr[i]));
    }
    //����char��ָ�������char��ά�������װ���Ա�readline��������
    //printf("%d\n", realline);
    unsigned long line[1023];

    //for test
    char tag_log_base[99][128] = { 0 };
    char* tag_log[99] = { 0 };
    for (int i = 0; i < 99; i++) {
        tag_log[i] = tag_log_base[i];
    }
    //for test end


    for (i = 0, line[0] = 0; i <= realline; i++) {

        line[i + 1] = readLine(text_ptr, out_ptr, debug, tag_log);
        if (line[i] == line[i + 1]) {
            printf("%d: ", line[i + 1]);
            puts(debug);
            break;
        }
    }
    //����readline��������.tcΪ.c

    fprintf(FileC, "%s\n", "#include<stdio.h>");
    fprintf(FileC, "%s\n", "#include<stdlib.h>");
    fprintf(FileC, "%s\n", "#include<string.h>");
    fprintf(FileC, "%s\n", "#include<math.h>");
    fprintf(FileC, "%s\n", "#include<time.h>");

    //������ȡʱ�亯��getTime
    fprintf(FileC, "%s\n", "char nowTime[32] = {0};");
    fprintf(FileC, "%s\n", "void getTime(char *nowTime){");
    fprintf(FileC, "%s\n", "char Year[5] = {0},Month[5] = {0},Day[5] = {0},Hour[5] = {0},Min[5] = {0},Sec[5] = {0};");
    fprintf(FileC, "%s\n", "time_t now;struct tm *ntime;time(&now);ntime = localtime(&now);");
    fprintf(FileC, "%s\n", "strftime(Year, sizeof(Year), \"%Y\", ntime);strftime(Month, sizeof(Month), \"%m\", ntime);");
    fprintf(FileC, "%s\n", "strftime(Day, sizeof(Day), \"%d\", ntime);strftime(Hour, sizeof(Hour),\"%H\", ntime);");
    fprintf(FileC, "%s\n", "strftime(Min, sizeof(Min),\"%M\", ntime);strftime(Sec, sizeof(Sec),\"%S\", ntime);");
    fprintf(FileC, "%s\n", "strcpy(nowTime, Year);strcat(nowTime, \"-\");strcat(nowTime, Month);strcat(nowTime, \"-\");");
    fprintf(FileC, "%s\n", "strcat(nowTime, Day);strcat(nowTime,\" \");strcat(nowTime, Hour);strcat(nowTime, \":\");");
    fprintf(FileC, "%s\n", "strcat(nowTime, Min);strcat(nowTime, \":\");strcat(nowTime, Sec);}");
    //�����浵����save
    fprintf(FileC, "%s\n", "char tag_log[99][128] = {0};");
    fprintf(FileC, "%s\n", "static int sceneCount = 0;");
    fprintf(FileC, "%s\n", "void save(int nowScene){");
    fprintf(FileC, "%s\n", "FILE* LoadFile = fopen(\"__load.txt\", \"w+\");");
    fprintf(FileC, "%s\n", "if(LoadFile==NULL){puts(\"Can not set up __load.txt!\\n\");exit(1);}");
    fprintf(FileC, "%s\n", "getTime(nowTime);");
    fprintf(FileC, "%s\n", "fprintf(LoadFile, \"%d,%s\", nowScene, nowTime);}");
    //edit by zht start ʹ�ô浵�ļ�
    fprintf(FileC, "%s\n", "void judgeInput(int sceneCount,char nextLine){");//����save���������浵�����˳�
    fprintf(FileC, "%s\n", "\tif(nextLine == \'Q\'){");
    fprintf(FileC, "%s\n", "printf(\"***Are you sure to save and quit?***[y/n]\\n\");");
    fprintf(FileC, "%s\n", "char decide = getchar();");//new
    fprintf(FileC, "%s\n", "while(getchar()!=\'\\n\');");//new
    fprintf(FileC, "%s\n", "if(decide !='y'){return;}");
    fprintf(FileC, "%s\n", "else{if(sceneCount>=1){save(sceneCount-1);}\nelse{save(0);}exit(0); }\n}");
    fprintf(FileC, "%s\n", "else if(nextLine == \'S\'){if(sceneCount>=1){save(sceneCount-1);}\nelse{save(0);}}}");
    //edit by zht end

    fprintf(FileC, "%s\n", "int main()");
    fprintf(FileC, "%s\n", "{");

    //edit by zht start
    fprintf(FileC, "int %s = 0;\n", "__load");
    fprintf(FileC, "int %s = 0;\n", "lastTag");
    fprintf(FileC, "char %s = 0;\n", "nextLine");
    fprintf(FileC, "char %s = 0;\n", "judgeLine");
    fprintf(FileC, "%s\n", "printf(\"Do you want to load?[y/n]\\n\");char input = getchar();while(getchar()!=\'\\n\');");
    fprintf(FileC, "%s\n", "if(input==\'y\'){FILE *LoadFile = fopen(\"__load.txt\", \"r\");char load_data[1024];fgets(load_data, 99, LoadFile);");
    fprintf(FileC, "%s\n", "char *_comma_ = strchr(load_data, \',\');printf(\"Load your last save at %s?[y/n]\\n\",_comma_+1);");
    fprintf(FileC, "%s\n", "input = getchar();while (getchar() != \'\\n\');if(input == \'y\'){__load = 1;*_comma_ = \'\\0\';");
    fprintf(FileC, "%s\n", "lastTag = atoi(load_data);}}");
    //edit by zht end

    //����.c�ļ�ͷ������

    for (i = 0; i < writeLine; i++) {

        //printf("%s", out_ptr[i]);//stdout���Լ��

        fprintf(FileC, "%s\n", out_ptr[i]);//д�뵽output.c��

    }
    //��readline����õ�c����д��output.c

    fprintf(FileC, "%s\n", "printf(\"The End. Any key to quit.\");getchar();}");
    //.c�ļ���β
    printf("Enter to continue.");
    getchar();
    getchar();


}

char* delete_end_blank(char* str, char* end_ptr)
{
    //��ͷ�����пո���Ԥ�����ʱ���Ѿ���ȥ�����������ԭʼ��俪ͷ��Ϊ�ո����һ���ַ�Ϊ@���������˺��������Ҳ�����ڴ����
    while (end_ptr != NULL && *(end_ptr) == ' ') {
        *end_ptr = '\0';
        end_ptr--;
    }
    return str;
}
int count_bracket(char* readed) {
    char* left;
    char* right;
    int leftc = 0;
    int rightc = 0;
    left = strchr(readed, '{');
    right = strchr(readed, '}');
    while (left != NULL) {
        leftc++;
        left = strchr(left + 1, '{');
    }
    while (right != NULL) {
        rightc++;
        right = strchr(right + 1, '}');
    }
    return leftc - rightc;
}

void delete_blank(char* str)
{
    char* str_c = str;
    int i, j = 0, flag = 0;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != ' ' && str[i] != '\t') {
            flag = i;
            break;
        }
    }
    for (i = flag; str[i] != '\0'; i++) {
        str_c[j++] = str[i];

    }
    str_c[j] = '\0';
    str = str_c;
}

void preprocessing(char original_text[][1023])
{
    FILE* fp;
    fp = fopen("taleC.tc", "r");
    if (fp == NULL) {
        puts("Cannot open file taleC.tc!");
    }
    int i;
    for (i = 0; i < MAX_CODE_LINE; i++) {
        fgets(original_text[i], MAX_CODE_LINE, fp);
        delete_blank(original_text[i]);
        if (original_text[i][0] != '\0')
            realline = i;
        original_text[i][strlen(original_text[i]) - 1] = '\0';
        //        printf("%s", original_text[i]);
        //        printf("%d\n", strlen(original_text[i]));
    }
    realline++;
    fclose(fp);
}

unsigned long readLine(char* src[], char* dst[], char* debug_log, char* tag_log[])
//ԭ�ַ������飬Ŀ�����飬����bugʱ����bug��Ϣ������
{
    static unsigned long readLine = 0;
    static unsigned int sceneTag = 0;
    static int scene_start = 0;
    static int bracket_count = 0;
    //����Ϊ�ڽ��ľ�̬������readline���ڷ��ض���������sceneTag��ÿ�δ���scene�ṹʱ������tag��ַ
    //scene_start�ǳ����������bracket_count�ǻ����ż������

    char readed[1025] = { 0 };
    char thisLine[1025] = { 0 };
    char tag[64] = { 0 };
    char* finder = NULL;
    int index = 0;
    char* quotefinder = NULL;
    char* right_parenthes = NULL;
    int length = strlen(src[readLine]);
    //    length--;
    if (length > 1024)
    {
        debug_log = "[error]: Too many chars in a line.";
        return readLine;
    }

    strcpy(readed, src[readLine]);

    bracket_count += count_bracket(readed);

    switch (readed[0])
    {
    case '$'://taleC $�﷨ ��Ҫ��Ұ��������������
        strcpy(dst[writeLine], "nextLine = ';';judgeLine = getchar();while (judgeLine != \'\\n\'){nextLine = judgeLine;judgeLine = getchar();};judgeInput(sceneCount,nextLine);");
        writeLine++;
        readLine++;
        return readLine;

    case '\"':
        /*---Enhanced code begin here---*/

        //�����ж��Ƿ���taleC@�﷨
        if ((finder = strchr(readed, '@')) == NULL)
        {
        Escape_char:
            if (readed[length - 1] == '\"')
            {
                strcpy(dst[writeLine], "printf(");
                strcat(dst[writeLine], readed);
                strcat(dst[writeLine], ");printf(\"\\n\");");
                writeLine++;
                readLine++;
                return readLine;
            }
            //��ȡ��taleC�﷨ "" ��дΪ��ӡ�ַ���������ݵ�һ�в����е�C����

            else if (readed[length - 1] == '\\' && readed[length - 2] == '\"')
            {
                readed[length - 1] = '\0';
                strcpy(dst[writeLine], "printf(");
                strcat(dst[writeLine], readed);
                strcat(dst[writeLine], ");");
                writeLine++;
                readLine++;
                return readLine;
            }
            //��ȡ��taleC�﷨ ""\  ��дΪ��ӡ�ַ��������ݵ�һ����������

            else
            {
                debug_log = "[error]: A \" needed.";
                return readLine;
            }
            //�﷨���󣬲���������������error�����ͬ��
            break;
        }
        else {//֧��taleC " " @() ""�﷨
            if (finder - 1 == NULL)
            {
                debug_log = "[error]: wrong @ at the head.";
            }
            else
            {//ת���ַ�\@
                if (*(finder - 1) == '\\')
                {
                    goto Escape_char;
                }
                else
                {//��ת���ַ�����ʼƥ��
                    quotefinder = strchr(readed + 1, '\"');
                    if (quotefinder != NULL && ((finder - quotefinder) > 0))
                    {
                        *quotefinder = '\0';
                        strcpy(tag, readed);
                        strcpy(dst[writeLine], "printf(");
                        strcat(dst[writeLine], tag);
                        //strcat(dst[writeLine], "\");");
                        switch (*(finder + 1))
                        {
                        case ':':
                            strcat(dst[writeLine], ": ");
                            goto Handle_left_str;
                            break;

                        case '>':
                            strcat(dst[writeLine], "> ");
                            goto Handle_left_str;
                            break;

                            //����Ϊ�Զ���ָ�����@�﷨
                        case '(':
                            right_parenthes = strchr(src[readLine], ')');
                            if (right_parenthes == NULL)
                            {
                                debug_log = "[error]: \')\' of an @ needed.";
                                return readLine;
                            }
                            else
                            {
                                *right_parenthes = '\0';
                                strcat(dst[writeLine], (finder + 2));
                                goto Handle_left_str;
                            }
                            break;


                        default:
                            debug_log = "[error]: wrong \'@\' used.";
                            return readLine;

                            //����ʣ�µ��ַ�����
                        Handle_left_str:
                            {
                                char* left_quotation_mark = strchr(finder, '\"');
                                char* right_quotation_mark = strchr(left_quotation_mark + 1, '\"');
                                if (left_quotation_mark == NULL)
                                {
                                    debug_log = "[error]: a string after @rule needed.";
                                    return readLine;
                                }
                                if (right_quotation_mark == NULL)
                                {
                                    debug_log = "[error]: another \" needed.";
                                    return readLine;
                                }
                                *right_quotation_mark = '\0';
                                strcat(dst[writeLine], left_quotation_mark + 1);
                                if (*(right_quotation_mark + 1) == '\\')
                                {
                                    strcat(dst[writeLine], "\");");
                                }
                                else
                                {
                                    strcat(dst[writeLine], "\\n\");");
                                }

                                readLine++;
                                writeLine++;
                                return readLine;
                            }
                        }
                    }
                    else
                    {
                        debug_log = "[error]: miss a \".";
                        return readLine;
                    }

                }
            }

        }
        /*---Enhanced code end here---*/

    case 'S':
    {
        int judge = strncmp("Scene", src[readLine], 5);
        if (judge)
        {
            goto DEFAULT;
            //���ֲ���taleC������Scene��ת�Ƹ�default
        }

        else
        {
            if (scene_start == 1)
            {
                debug_log = "[error]: last scene lack a }";
                return readLine;
            }
            scene_start = 1;
            //bracket_count = 1;

            char* left_parenthes = strchr(src[readLine], '(');
            char* right_parenthes = strchr(left_parenthes + 1, ')'); //src[readLine]��ԭ�ȵĵ�һ������
            //Ѱ����������
            if (left_parenthes == NULL || right_parenthes == NULL)
            {
                debug_log = "[error]: \'(\' or \')\' needed.";
                return readLine;
            }
            //Բ���Ų�ȫ�����bug
            *right_parenthes = '\0';
            //char var_combined_by_comma[1024];
            char scene_name[64] = { 0 };
            strcpy(scene_name, left_parenthes + 1);
            *right_parenthes = ')';
            //char* token;
            //token = strtok(var_combined_by_comma, ", ");
            strcpy(dst[writeLine], scene_name);
            strcpy(tag_log[sceneTag], scene_name);
            strcat(dst[writeLine], ":");
            strcat(dst[writeLine], "{int ");
            // token = strtok(NULL, var_combined_by_comma);
             //while (token != NULL)
             //{
              //   strcat(dst[writeLine], token);
              //   strcat(dst[writeLine], "=0,");
              //   token = strtok(NULL, var_combined_by_comma);
              //   if (token == NULL) {
              //       ;
             //    }
              //   else {
              //       token--;
             //   }
            // }
             //Ϊscene������ʼ���¼������������ʼ����һ�����ر���scene_tag��

            strcat(dst[writeLine], "scene_tag = ");
            char numList[13];//һ��long�����12λ��
            itoa(sceneTag++, numList, 10);
            strcat(dst[writeLine], numList);
            strcat(dst[writeLine], ";");
            writeLine++;
            strcpy(dst[writeLine], "strcpy(tag_log[sceneCount], \"");
            strcat(dst[writeLine], scene_name);
            strcat(dst[writeLine], "\");");
            writeLine++;
            strcpy(dst[writeLine], "sceneCount++;");
            writeLine++;
            strcpy(dst[writeLine], "if(__load == 1 && scene_tag<lastTag){goto ");
            strcat(dst[writeLine], scene_name);
            strcat(dst[writeLine], "_end;}");
            writeLine++;

            readLine++;
            return readLine;
        }
        break;
    }
    case '}':

        if (scene_start == 0) {
            goto DEFAULT;
        }
        if (scene_start == 1 && bracket_count == 0)
        {//scene end
            strcpy(dst[writeLine], readed);
            writeLine++;
            strcpy(dst[writeLine], tag_log[sceneTag - 1]);
            strcat(dst[writeLine], "_end:;");
            writeLine++;
            readLine++;
            scene_start = 0;
            return readLine;
        }
        else if (scene_start == 1 && bracket_count) {
            debug_log = "[error]: lack a {";
            return readLine;
        }
        break;
    default:
        //���Ｏ�д��������ĸ�޷������Ƿ���taleC�﷨����
    DEFAULT:
    {
        strcpy(thisLine, src[readLine]);
        char* finder;
        //�����ж��Ƿ���taleC@�﷨
        if ((finder = strchr(thisLine, '@')) != NULL)
        {
            if (*(finder - 1) != '\\')
            {//����@����Ϊת���ַ���ƥ��ΪtaleC�﷨
                //���@ǰ��tag
                switch (*(finder + 1))
                {//��@ǰ���ַ�ʶ��Ϊ������
                case ':':
                    *finder = '\0';
                    //delete_end_blank
                    strcpy(dst[writeLine], "printf(\"%s: \",");
                    strcat(dst[writeLine], delete_end_blank(thisLine, finder - 1));//��@��ǰһ���ַ���ʼɾȥβ�ո�����ͬ��
                    strcat(dst[writeLine], ");");
                    goto Handle_left_string;
                    break;

                case '>':
                    *finder = '\0';
                    strcpy(dst[writeLine], "printf(\"%s> \",");
                    strcat(dst[writeLine], delete_end_blank(thisLine, finder - 1));
                    strcat(dst[writeLine], ");");
                    goto Handle_left_string;
                    break;

                    //����Ϊ�Զ���ָ�����@�﷨
                case '(':
                {
                    right_parenthes = strchr(thisLine, ')');
                    if (right_parenthes == NULL) {
                        debug_log = "[error]: \')\' of an @ needed.";
                        return readLine;
                    }
                    else
                    {
                        *finder = '\0';
                        *right_parenthes = '\0';
                        strcpy(dst[writeLine], "printf(\"%s");
                        strcat(dst[writeLine], (finder + 2));
                        strcat(dst[writeLine], "\",");
                        strcat(dst[writeLine], delete_end_blank(thisLine, finder - 1));
                        strcat(dst[writeLine], ");");
                        //�൱��printf("%s(�Զ���ָ���)", tag);
                        goto Handle_left_string;
                    }
                    break;
                }

                default:
                    debug_log = "[error]: wrong \'@\' used.";
                    return readLine;

                    //����ʣ�µ��ַ�����
                Handle_left_string: {
                    char* left_quotation_mark = strchr(readed, '\"');
                    char* right_quotation_mark = strchr(left_quotation_mark + 1, '\"');
                    if (left_quotation_mark == NULL)
                    {
                        debug_log = "[error]: a string after @rule needed.";
                        return readLine;
                    }
                    if (right_quotation_mark == NULL)
                    {
                        debug_log = "[error]: another \" needed.";
                        return readLine;
                    }
                    *right_quotation_mark = '\0';
                    strcat(dst[writeLine], "printf(");
                    strcat(dst[writeLine], left_quotation_mark);
                    if (*(right_quotation_mark + 1) == '\\')
                    {
                        strcat(dst[writeLine], "\");");
                    }
                    else {
                        strcat(dst[writeLine], "\\n\");");
                    }

                    readLine++;
                    writeLine++;
                    return readLine;
                    }
                }
            }
            else
            {
                goto Escape_character;
            }
        }
        else
        {
            //����Ϊ��@�﷨������У�����ת���ַ�\@����ֱ�ӿ�����C����
        Escape_character:
            strcpy(dst[writeLine], thisLine);
            readLine++;
            writeLine++;
            return readLine;
        }
    }
    }
}