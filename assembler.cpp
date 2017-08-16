/*
 * assembler.cpp
 * 
 * 
 * 
 */


#include <bits/stdc++.h>

using namespace std;

string address[1000];
int locctr=0;

string SYMTAB[100][3];
string program_len;
string OPTAB[45][3]={"ADD","18","3",
                     "ADDR","90","2",
                     "AND","40","3",
                     "CLEAR","B4","2",
                     "COMP","28","3",
                     "COMPR","A0","2",
                     "DIV","24","3",
                     "DIVR","9C","2",
                     "J","3C","3",
                     "JEQ","30","3",
                     "JGT","34","3",
                     "JLT","38","3",
                     "JSUB","48","3",
                     "LDA","00","3",
                     "LDB","68","3",
                     "LDCH","50","3",
                     "LDL","08","3",
                     "LDS","6C","3",
                     "LDT","74","3",
                     "LDX","04","3",
                     "LPS","D0","3",
                     "MUL","20","3",
                     "MULR","98","2",
                     "OR","44","3",
                     "RD","D8","3",
                     "RMO","AC","2",
                     "RSUB","4C","3",
                     "SHIFTL","A4","2",
                     "SHIFTR","A8","2",
                     "STA","0C","3",
                     "STB","78","3",
                     "STCH","54","3",
                     "STI","D4","3",
                     "STL","14","3",
                     "STS","7C","3",
                     "STSW","E8","3",
                     "STT","84","3",
                     "STX","10","3",
                     "SUB","1C","3",
                     "SUBR","94","2",
                     "SVC","B0","2",
                     "TD","E0","3",
                     "TIX","2C","3",
                     "TIXR","B8","2",
                     "WD","DC","3"};

string to_hex(int p)
{
    long int j;
    char q1;
    string hex;
    while(p!=0)
    {
        j = p%16;
        switch (j)
        {
            case 10:q1 = 'A';break;
            case 11:q1 = 'B';break;
            case 12:q1 = 'C';break;
            case 13:q1 = 'D';break;
            case 14:q1 = 'E';break;
            case 15:q1 = 'F';break;
            default :q1 = j+'0';break;
        }
        hex += q1;
        p = p/16;
    }
    int m = hex.length();
    char z;
    for(int i =0;i<m/2;i++)
    {
        z = hex[m-i-1];
        hex[m-i-1] = hex[i];
        hex[i] =  z;
    }
    return hex;
}

int str_to_int(string addr){
	int temp = addr.length();
	int temp1=0;
	int ans=0;
	for(int i=0; i<temp; ++i){
		if(addr[i]-'0'<=9){
			temp1=addr[i]-'0';
		}else{
			if(addr[i]=='A') temp1 = 10;
			if(addr[i]=='B') temp1 = 11;
			if(addr[i]=='C') temp1 = 12;
			if(addr[i]=='D') temp1 = 13;
			if(addr[i]=='E') temp1 = 14;
			if(addr[i]=='F') temp1 = 15;
		}
		ans = ans + temp1*pow(16,temp-i-1);
	}
	return ans;
}

int stoi(string addr){
	int temp = addr.length();
	int temp1=0;
	int ans=0;
	for(int i=0; i<temp; ++i){
		if(addr[i]-'0'<=9){
			temp1=addr[i]-'0';
		}
		ans = ans + temp1*pow(10,temp-i-1);
	}
	return ans;
}

bool CheckOPTAB(string a)
{
    for(int i=0;i<45;i++){
       if(OPTAB[i][0]==a) return 1;
    }
    return 0;
}

string search_OPTAB(string a){
	for(int i=0;i<45;i++){
       if(OPTAB[i][0]==a) return OPTAB[i][1];
    }
    return "";
}

bool CheckSYMTAB(string a)
{
    int c=0;
    while(SYMTAB[c][0]!="END")
    {
        if(SYMTAB[c][0]==a)
        return 1;
        c++;
    }
    return 0;
}

string search_SYMTAB(string a){
	int c=0;
    while(SYMTAB[c][0]!="END")
    {
        if(SYMTAB[c][0]==a)
        return SYMTAB[c][1];
        c++;
    }
    return "";
}

void Insert_SYMTAB(string a)
{
    int c=0;
    while(SYMTAB[c][0]!="END")
    {
        c++;
    }
    SYMTAB[c][0]=a;
    SYMTAB[c+1][0]="END";
    return;
}

void Insert_SYMTAB_Addr(string a,string addr)
{
    int c=0;
    while(SYMTAB[c][0]!="END")
    {
        if(SYMTAB[c][0]==a)
        {
            SYMTAB[c][1]=addr;
            return;
        }
        c++;
    }
    SYMTAB[c][0]=a;
    SYMTAB[c][1]=addr;
    SYMTAB[c+1][0]="END";
}

vector < string > parse_data(string str){
	unsigned int a = 0;
	vector < string > ans;
	string temp;
	while(a<str.size()){
		temp = "";
		while(a<str.size() && (str[a]!=' ' && str[a]!='\t')){
			temp += str[a++];if(a==str.size())		break;
		}
		while(a<str.size() && (str[a]==' ' || str[a]=='\t')){
			a++;
			if(a==str.size()) break;
		}
		if(temp!="")		ans.push_back(temp);
		if(a==str.size())	break;
	}
	return ans;
}

void pass1(){
	ifstream in;
	ofstream out("intermediate.txt");
	string str;
	SYMTAB[0][0]="START";
    SYMTAB[1][0]="END";
	in.open("input.txt");
	getline(in, str);
	int line=0, init_addr;
	vector<string> v = parse_data(str);
			if(v[1]=="START"){
				address[0] = v[2];
				address[1] = v[2];
				locctr = str_to_int(v[2]);
			}else{
				locctr = 0;
			}
	init_addr = locctr;
	string addr = to_hex(locctr);
	string write_out = addr;
	out<<write_out<<"\t"<<v[0]<<"\t"<<v[1]<<"\t"<<v[2]<<endl;
	v.clear();
	while(true){
		addr = to_hex(locctr);
		v.clear();
		getline(in, str);
		line++;
		v = parse_data(str);
		if(v[0]=="."){
			continue;
		}
		if(v.size()==3){
			if(CheckSYMTAB(v[0])){
				//error
			}else{
				Insert_SYMTAB(v[0]);
				Insert_SYMTAB_Addr(v[0], to_hex(locctr));
			}
			if(CheckOPTAB(v[1])){
				locctr+=3;
			}else if(v[1]=="WORD"){
				locctr+=3;
			}else if(v[1]=="RESW"){
				locctr = locctr + 3*stoi(v[2]);
			}else if(v[1]=="RESB"){
				locctr = locctr + stoi(v[2]);
			}else if(v[1]=="BYTE"){
				if(v[2][0]=='C'){
					locctr = locctr + v[2].length()-3;
				}else{
					locctr = locctr + (v[2].length()-3)/2;
				}
			}else{
				//error
			}
		}
		if(v.size()==2){
			if(CheckOPTAB(v[0])){
				locctr+=3;
			}else if(v[0]=="WORD"){
				locctr+=3;
			}else if(v[0]=="RESW"){
				locctr = locctr + 3*stoi(v[2]);
			}else if(v[0]=="RESB"){
				locctr = locctr + stoi(v[2]);
			}else if(v[0]=="BYTE"){
				if(v[1][0]=='C'){
					locctr = locctr + v[2].length()-3;
				}else{
					locctr = locctr + (v[2].length()-3)/2;
				}
			}else{
				//error
			}
		}
		if(v.size()==1){
			locctr+=3;
		}
		write_out = addr;
		
		if(v.size()==3){
			write_out = write_out + "\t" + v[1] + "\t" + v[2];
		}else{
			for(unsigned int i=0; i<v.size(); ++i){
			write_out = write_out + "\t" + v[i];
			}
		}
		out<<write_out<<endl;
		
		if(v[0]=="END") break;
	}
	int c=0;
	while(SYMTAB[c][0]!="END")
    {
        cout<<SYMTAB[c][0]<<"\t"<<SYMTAB[c][1]<<endl;
        c++;
    }
    program_len = to_hex(locctr-init_addr);
}

void pass2(){
	ifstream intermediate;
	ofstream output("object_code.txt");
	intermediate.open("intermediate.txt");
	string str, head_rec = "H", text_rec = "T", temp = "";
	getline(intermediate, str);
	vector<string> v = parse_data(str);
	if(v[2]=="START"){
		head_rec+=v[1];
		for(unsigned int i=0; i<6-v[1].length(); ++i){
			head_rec+=" ";
		}
		for(unsigned int i=0; i<6-v[0].length(); ++i){
			head_rec+="0";
		}
		head_rec+=v[0];
		for(unsigned int i=0; i<6-program_len.length(); ++i){
			head_rec+="0";
		}
		head_rec+=program_len;
	}
	output<<head_rec<<endl;
	string t_addr = v[0], init_addr = v[0];
	while(true){
		getline(intermediate, str);
		string prev_addr = v[0];
		v.clear();
		v = parse_data(str);
		string new_addr = v[0];
		int commaFlag=0;
		string opcode, object_opcode="", object_op_addr="", object_code_line="";
		opcode = v[1];
		if(opcode=="RESB"){
			for(unsigned int i=0; i<6-t_addr.length(); ++i){
				text_rec+="0";
			}
			text_rec+=t_addr;
			string length = to_hex(temp.length()/2);
			if(length.length()==2) text_rec+=length;
			if(length.length()==1) text_rec+= "0"+length;
			text_rec+=temp;
			t_addr = v[0];
			output<<text_rec<<endl;
			text_rec = "T";
			temp="";
		}
		if(v[1]=="END"){
			for(unsigned int i=0; i<6-t_addr.length(); ++i){
				text_rec+="0";
			}
			text_rec+=t_addr;
			string length = to_hex(temp.length()/2);
			if(length.length()==2) text_rec+=length;
			if(length.length()==1) text_rec+= "0"+length;
			text_rec+=temp;
			output<<text_rec<<endl;
			string end_rec = "E";
			for(unsigned int i=0; i<6-init_addr.length(); ++i){
				end_rec+="0";
			}
			end_rec+=init_addr;
			output<<end_rec<<endl;
			break;
		}
		

		if(CheckOPTAB(opcode)){
			object_opcode = search_OPTAB(opcode);
			if(v.size()==3){
				int comma_index = v[2].length()-2;
				if(v[2][comma_index]==','){
					commaFlag=1;
					string t  = "";
					for(int i=0; i<comma_index; ++i){
						t+=v[2][i];
					}
					v[2] = t;
				}
				if(CheckSYMTAB(v[2])){
					if(commaFlag==1){
						int buffer = str_to_int(search_SYMTAB(v[2]));
						int indexed = pow(2,15) + buffer;
						object_op_addr = to_hex(indexed);
					}
					object_op_addr = search_SYMTAB(v[2]);
				}else{
					object_op_addr="0000";
				}
			}else{
				object_op_addr = "0000";
			}
			object_code_line = object_opcode + object_op_addr;
		}else{
			string temp_line = "";
			if(opcode == "WORD"){
				temp_line= to_hex(stoi(v[2]));
				string tmp2 = temp_line;
				for(unsigned int i=0; i<6-tmp2.length(); ++i){
					temp_line = "0" + temp_line;
				}
			}else if(opcode == "BYTE"){
				if(v[2][0] == 'C'){
					for(unsigned int i=2; i<v[2].length()-1; ++i){
						temp_line += to_hex((int)v[2][i]);
					}
				}else{
					for(unsigned int i=2; i<v[2].length()-1; ++i){
						temp_line += v[2][i];
					}
				}
			}
			object_code_line = temp_line;
		}
		if(temp.length()+object_code_line.length()>60){
			for(unsigned int i=0; i<6-t_addr.length(); ++i){
				text_rec+="0";
			}
			text_rec+=t_addr;
			string length = to_hex(temp.length()/2);
			if(length.length()==2) text_rec+=length;
			if(length.length()==1) text_rec+= "0"+length;
			text_rec+=temp;
			t_addr = v[0];
			output<<text_rec<<endl;
			text_rec = "T";
			temp="";
		}
			temp+=object_code_line;
	}
}

int main(){
	pass1();
	pass2();
	return 0;
}
