/*
* @author: Kejian Shi ks4765
* @version: 1.1 
* @bug: getline() calls resize()
* @todo: personal goal: reproduce the strcmp implementation
*/

// #include "types.h"
// #include "user.h"
// #include "stat.h"


// // porc indicator imoportant

// const int ASCIIOP = 32; // for uppercase()
// int g_maxSize = 512; 
// int g_cflag = 0, g_dflag = 0, g_iflag = 0; 
// int g_resizeIndicator; 
// char* g_pPrev, * g_pCurr;
// /* line in an fd */ 

// void usage();
// void illegal(char);
// char* resize(char*, int);
// int getline(int fd, char*, int);
// char* uppercase(const char*);
// int strcmppro(char*, char*); 
// void output();
// void uniq(int);


// char* resize(char* buf, int g_resizeIndicator){
// 	g_maxSize *= 2;
// 	char* res = (char* )malloc(g_maxSize*sizeof(char));
// 	strcpy(res, buf);
// 	printf(1,"after strcpy\n");
// 	printf(1, "%d\n" , strlen(buf));
// 	free(buf);


// 	// new stuff added, key 
// 	if(g_resizeIndicator == 0){g_pPrev = res;}
// 	else{g_pCurr = res;}
// 	/*
// 	*/

// 	return res;
// }


// int getline(int fd, char* buf, int g_resizeIndicator){
// 	char aChar; 
// 	int cnt = 0; 
// 	int fdStatus = 1; //default to 1; 
// 	while((fdStatus = read(fd,&aChar,1)) > 0){
// 		if(cnt >= g_maxSize - 1){
// 			printf(1,"enter here\n");
// 			// char* buf = resize(buf); // should not init a new variable !!
// 			buf = resize(buf,g_resizeIndicator); 
// 		}
// 		if(aChar == '\n') break;
// 		buf[cnt++] = aChar;
	
// 	}
// 	if(fdStatus == -1) return -1; 
// 	if(fdStatus == 0){
// 		if(cnt > 0) goto addnull; // that means we read something and we should report it. 
// 		else return 0;
// 	}
// addnull:
// 	buf[cnt] = '\0';
// 	// int i; 
// 	// for(i = 0; buf[i] != '\0'; ++i){
// 	// 	printf(1,"%c\n",buf[i]);
// 	// }
// 	// printf(1,"the length is: %d\n",i+1);
// 	// printf(2, "inside output, the cnt is %d\n",cnt);
// 	return cnt; // how many bytes in the buf [0, ] 
// }

// /*@return: a;
// *
// */
// char* uppercase(const char* str){
// 	/* WARNING: invoke this funtion together with strcmppro(), otherwise memory leak */
// 	// can't change the original, we have to return a copy
// 	int i;
// 	char* res = (char*)malloc(sizeof(char) * g_maxSize);
// 	for(i = 0; str[i] != '\0' ; ++i){
// 		res[i] = str[i] >= 97 && str[i] <= 122  ? str[i] & ~ASCIIOP : str[i];	
// 	}
// 	return res; 
// }

// int strcmppro(char* lhs,  char* rhs){
// 	// check the return behavior of strcmp, using substraction
// 	int res = 1; //def not equal (1 == 0), res will be reset if the strlen is the same
// 	if(strlen(lhs) == strlen(rhs)){
// 		if(g_iflag){
// 			char* uplhs = uppercase(lhs); 
// 			char* uprhs = uppercase(rhs);
// 			res = strcmp(uplhs, uprhs);
// 			free(uplhs);
// 			free(uprhs);
// 		}else{
// 			res = strcmp(lhs,rhs);
// 		}
// 	}
// 	return (res == 0);
// }

// void illflag(char badFlag){
// 	printf(2, "uniq: illegal option -- %c\n", badFlag);
// }
// void usage(){
// 	printf(2, "usage: uniq [-c | -d ] [-i] [input [output]]\n");
// }


// void output(char* buf, int cnt){
// 	// check what's inside the buffer 
// 	// int i; 
// 	// for(i = 0; buf[i]; ++i){
// 	// 	printf(1,"%c\n",buf[i]);
// 	// }
// 	// printf(1,"the length is: %d",i);

// 	// printf(2, "inside output, the cnt is %d\n",cnt);
// 	if(g_cflag){ //we can guarantee c and d flag won't appear at the same time
// 		// printf(1,"inside g_cflag\n");
// 		// printf(1, "%4d %s\n",cnt,buf);
// 		printf(1,"   %d\t %s\n",cnt,buf);
// 	}else{
// 		printf(1, "%s\n",buf);
// 	}
// }

// void uniq(int fd){

// 	// 
// 	// printf(2, "in uniq\n");
// 	char* tmp;
// 	int cntSeen = 1;
// 	int fdmsg;
// 	g_pPrev = (char* )malloc(sizeof(char) * g_maxSize);
// 	printf(2,"initialized prev size is %d\n", sizeof(g_pPrev));
// 	if ((fdmsg = getline(fd,g_pPrev,0)) <= 0){
// 		// printf(2, "in uniq if\n");
// 		usage(); 
// 		exit();
// 	} 
// 	g_pCurr = (char* )malloc(sizeof(char)* g_maxSize);
// 	printf(2,"initialized curr size is %d\n", sizeof(g_pCurr));


// 	while((fdmsg = getline(fd,g_pCurr,1)) > 0){
// 		// printf(2, "in uniq while\n");
		
// 		if(strcmppro(g_pPrev,g_pCurr)){
// 			cntSeen++;

// 			// 巧妙的修复，当 -i 时（或其他时候）先出现的得到保留，那一直留着 g_pPrev即可
// 			free(g_pCurr);

// 			g_pCurr = (char* )malloc(sizeof(char)* g_maxSize);
// 			continue;
// 		}
// 		if( (!g_dflag) || (g_dflag && cntSeen > 1)) {  output(g_pPrev,cntSeen); }
// 		cntSeen = 1;
// 		tmp = g_pPrev;
// 		g_pPrev = g_pCurr;
// 		free(tmp);
// 		g_pCurr = (char* )malloc(sizeof(char)* g_maxSize);
// 	}
// 	if( (!g_dflag) || (g_dflag && cntSeen > 1)) {output(g_pPrev,cntSeen); }
// 	free(g_pPrev); 
// 	free(g_pCurr);

// 	//  !!!! Big： getline 大while ， 里面 prev = curr 小while,  没有新的line 被持续get 怎么可能可以一直prev = curr
// 	//  肯定不能再套了， if 
// 	// 	while(strcmppro(g_pPrev,g_pCurr)){
// 	// 		cntSeen++;
// 	// 		tmp = g_pPrev;
// 	// 		g_pPrev = g_pCurr;
// 	// 		free(tmp);
// 	// 	}
// 	// 	if( (!g_dflag) || (g_dflag && cntSeen > 1) ) output(g_pPrev,cntSeen);
// 	// 	cntSeen = 1;
// 	// 	tmp = g_pPrev;
// 	// 	g_pPrev = g_pCurr;
// 	// 	free(tmp);
// 	// }
// 	// if( (!g_dflag) || (g_dflag && cntSeen > 1) ) output(g_pPrev,cntSeen);
// 	// free(g_pPrev);
// }


// int main(int argc, char** argv){
// 	printf(1,"Running uniq main()\n");
// 	// printf(1,"Testing uppercase()\n");

// 	// char buffer[512]; 
// 	// g_pPrev = (char* )malloc(sizeof(char) * g_maxSize);
// 	// printf(1,"after init, the array prev pointed to is size of %d", sizeof(g_pPrev));
// 	// int fd = open("example.txt", 0);
// 	// // int fd = 0;
// 	// printf(1,"fd is %d\n",fd);
// 	// getline(fd,g_pPrev);
// 	// free(g_pPrev);
	
// 	// int cf;
// 	// int i; 
// 	// while((cf = getline(fd,buffer)) > 0){
// 	// 	for(i = 0; buffer[i]; i++){
// 	// 		printf(1,"%c", buffer[i]);
// 	// 	}
// 	// 	printf(1,"\n");
// 	// }
// 	// printf(1,"after while");
	
// 	/*
// 	* Testing strcmppro;
// 	*/
//     // char buf[] = "abcd";
// 	// char buf2[] = "AbcD";
// 	// printf(1,"The result without i flag: %d\n", strcmppro(buf,buf2));
// 	// g_iflag = 1;
// 	// printf(1,"The result with i flag %d\n", strcmppro(buf,buf2));

// 	// printf(1, "%d\n", g_maxSize);
// 	// printf(1, "%d\n", g_maxSize--);
// 	// printf(1, "%d\n", g_maxSize);	
// 	// 512 
// 	// 512, bc store first, so the origina value printed out 
// 	// 511

// 	// Go to notes  char buf[512]; sizeof buf = 512
// 	// char buf2[1];
// 	// int i;
// 	// for(i = 0; i < 10;++i){
// 	// 	buf2[i] = 1;
// 	// }
// 	// sizeof buf2 = 1;

// 	// char* test = (char*) malloc(sizeof(char) * g_maxSize);
// 	// test = "no. 1";
// 	// char* res = uppercase(test);
// 	// printf(1, "%s\n", res);

// 	int fd = 0; 
// 	int i;
// /*  */
// 	for(i = 1; i < argc; ++i){
// 		// printf(1,"%d\n",sizeof(*argv[i])); // *argv[i] will be a char
// 		// //!!!! 这样永远是 1 ！！因为你dereferene 的是那一个char 而已， 所以用strlen可以
// 		// printf(1,"%d\n",strlen(argv[i]));
// 		if(argv[i][0] == '-'){
// 			switch(argv[i][1])
// 			{
// 				case('c'):
// 					// printf(1,"cflg is on");
// 					g_cflag = 1;
// 					continue;

// 				case('d'):
// 					// printf(1,"dflg is on");
// 					g_dflag = 1;
// 					continue;

// 				case('i'):
// 					// printf(1,"iflg is on");
// 					g_iflag = 1;
// 					continue;
// 				default:
// 					if (strlen(argv[i]) >= 2) { // unknown flag is input in args
// 						illflag(argv[i][1]);
// 						usage();
// 						exit();
// 					} else{
// 						exit();
// 					}	
// 			}
// 		}else {
// 			if((fd = open(argv[i],0)) == -1){ usage(); exit();} // 0 for O_RDONLY
// 		}
// 	}
// 	if(g_cflag && g_dflag) { usage(); exit(); } 
// 	uniq(fd);
// 	close(fd);
// 	exit();
// }

 

// #include "types.h"
// #include "stat.h"
// #include "user.h"

// int maxSize = 512;  
// char* prevl, *currl; // has to write both * for static typing 
// int cflag = 0, dflag = 0, iflag = 0; 


// // 此code 亮点 
// //	1. global variable反复被更新
// //	2. 非常好的 OO design
// //  3. C convention 的和好的诠释: 如 (if foo() < 0) 
// //


#include "types.h"
#include "stat.h"
#include "user.h"
int maxSize = 1024;
char *prevline, *curline;
int cflag = 0, dflag = 0, iflag = 0;

// porc == 1: curline
// porc == 0: prevline
char* resize_buf(char* buf, int porc){
	maxSize *= 2;
	char* res = strcpy(malloc(sizeof(char)*maxSize),buf);
	free(buf);
	if(porc == 1){curline = res;}
	else{prevline = res;}
	return res;
}

// fd = file descriptor
// cf = check file
// porc == 1: curline
// porc == 0: prevline
int getline(int fd, char * buf, int count, int porc){
	int i = 0;
	int cf; 
	// i is the total number of bytes of the buffer
	// count is maxSize varible = 512; 
	char c; 
 	while(i < count){// keep reading 
		cf = read(fd, &c, 1); // return #bytes read on success (0 is the end), -1 is error; // read character by character 
		if(cf < 1){ // either end of file or error 
			if(i != 0){  // if something has read before in this getLine
				buf[i++] = '\n'; // we add a newLine for the convenience to print 
				break; 
			}
			return (-1); // if error then return -1, or it could be 0, meaning the end of file right? 
		}
		buf[i++] = c;
		if(c == '\n'){ break; }
		if(i == count - 1){
			count *= 2;
			maxSize = count;
			buf = resize_buf(buf, porc);
		}
	}
	buf[i] = '\0'; // '\0' is NULL	
	return i; 
	// // how many bytes in the buf [0, ] 
	// remark: strlen is another implementation, it will check for (i = 0, s[n] != '\0', ++i)
	
}

void output(char* line, int num_seen){
	if(cflag){
		printf(1, "%4d %s", num_seen, line);
	}else{
		printf(1, "%s", line);
	}
}

char to_lower(char ch) {
	return (ch <= 'Z' && ch >= 'A') ? ch + 32 : ch;
}

// case insensitive check for strcmp
// return equal ? 0 else some_int
int strcmpCase(const char* p, const char* c){
	const char* s1 = p;
	const char* s2 = c;
	while(*s1 != '\0'){
		int d = to_lower(*s1++) - to_lower(*s2++);
		if(d){ return d; } 
	}
	if(*s2 == '\0'){ return 0; }
  	return 1;
}


int not_equal(char* p, char* c){
	// iflag -- case insensitive
	return (iflag) ? strcmpCase(p, c) : strcmp(p,c);
}

void uniq(int fd){
	char* swap;
	int num_seen = 1;
	char* prevline = (char* )malloc(sizeof(char)*maxSize);
	if( getline(fd,prevline,maxSize,0) < 0 ){ free(prevline);exit(); }//try to read the first line. 
	// !!!!!!!! !!!! prevlinrwe是一部分memory,!!!!!
	// C 重要
	//!!! 
	
	// getline returns the total length of the buffer: that is stelen + 1 
	char* curline = (char* )malloc(sizeof(char)*maxSize);

	while( getline(fd,curline,maxSize,1) > 0 ){ // when we are not done 
		if(not_equal(prevline,curline)){
			// for dflag, we only print lines that appear multiple times
			if((dflag && num_seen > 1) || !dflag){ output(prevline,num_seen); }
			// Swap and reset num_seen
			swap = curline;
			curline = prevline;
			prevline = swap;
			num_seen = 1;
		}else{
			num_seen++;
		}
	}
	if((dflag && num_seen > 1) || !dflag){
		output(prevline,num_seen);
	}
	free(prevline); free(curline);
}

void usage(){
	printf(2, "%s\n%s\n%s\n%s\n%s\n", 
			"[USAGE]: uniq [-c] [-d] [-i] filename",
			"[USAGE]: -c and -d flag cannot be used at the same time",
			"[FLAG]-c --count: display the counts for each line",
			"[FLAG]-d --duplicate: only display duplicate lines",
			"[FLAG]-i --ignore: perform case insensitive uniq"
		);
}

int main(int argc, char * argv[]){
	int fd = 0;
    int i = 1;
    for(; i < argc; ++i)
    {
    	if(argv[i][0] == '-')
    	{
    		switch(argv[i][1])
    		{
    			case 'c': cflag = 1; continue;
    			case 'd': dflag = 1; continue;
    			case 'i': iflag = 1; continue;
    			default: 
    				usage(); 
    				exit();
    		}
    	}
    	else{
    		if((fd = open(argv[i], 0)) < 0)
    		{
		        printf(1, "[WARNING] uniq: cannot open %s\n", argv[i]);
		        usage();
				exit();
		    }
		}
    }
    if(cflag && dflag){usage();exit();}
	uniq(fd);
	if(fd){ close(fd); }
	exit();
}