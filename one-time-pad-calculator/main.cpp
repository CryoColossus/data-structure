#include <iostream>
using namespace std;
void initialize(string &cipher,string &key,int &cipher_format,int &key_format)
{
    cout<<"What format will your plaintext be in? (1 for hexadecimal)"<<endl;
    cin>>cipher_format;
    cout<<"Enter your Plaintext"<<endl;
    cin>>cipher;
    cout<<"What format will your key be in? (1 for hexadecimal)"<<endl;
    cin>>key_format;
    cout<<"Enter your One Time Pad Key"<<endl;
    cin>>key;
}
string hex_char_to_bin(char c)
{
    switch(toupper(c))
    {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
    }
    return "";
}
char bin_bits_to_hex(string s)
{
    if(s=="0000") return '0';
    else if(s=="0001") return '1';
    else if(s=="0010") return '2';
    else if(s=="0011") return '3';
    else if(s=="0100") return '4';
    else if(s=="0101") return '5';
    else if(s=="0110") return '6';
    else if(s=="0111") return '7';
    else if(s=="1000") return '8';
    else if(s=="1001") return '9';
    else if(s=="1010") return 'A';
    else if(s=="1011") return 'B';
    else if(s=="1100") return 'C';
    else if(s=="1101") return 'D';
    else if(s=="1110") return 'E';
    else if(s=="1111") return 'F';
    else return ' ';
}
void hex_to_bin(string &str)
{
    string new_str="";
    if(str.length()%2==0)
        for(int i=0;i<str.length();i++)
            new_str = new_str + hex_char_to_bin(str[i]);
    //cout<<"For string "<<str<<" the new string is "<<new_str<<endl;  
    str = new_str;
}
void bin_to_hex(string &str)
{
    string new_str="";
    if(str.length()%4==0)
        for(int i=0;i<str.length();i+=4)
        {
            new_str = new_str + bin_bits_to_hex(str.substr(i,4));
        }
    str = new_str;    
}
void make_binary(string &str,int type)
{
    switch(type)
    {
        case 1: return hex_to_bin(str);
        break;
    }
}
string XOR(string cipher,string key)
{
    string s="";
    if(cipher.length()==key.length())
        for(int i=0;i<cipher.length();i++)
            s = s+(char)(((cipher[i]-'0')^(key[i]-'0'))+'0');
    return s;
}
int main()
{
    int cipher_format,key_format;
    string cipher,key,ciphertext;
    initialize(cipher,key,cipher_format,key_format);
    make_binary(cipher,cipher_format);
    make_binary(key,key_format);
    ciphertext = XOR(cipher,key);
    cout<<"Your Encrypted Ciphertext (In Binary): "<<ciphertext<<endl; 
    bin_to_hex(ciphertext);
    cout<<"Your Encrypted Ciphertext (In Hexadecimal): "<<ciphertext<<endl; 
    return 0;
}