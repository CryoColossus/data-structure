import java.util.*;
import java.io.IOException;
class Btnode
{
    Btnode lc;
    String data;
    int freq;
    Btnode rc;
}
class BinaryTree
{
    Btnode root;
    int i=0;
    Btnode create(String s, Btnode node) throws IOException
    {
        if(node == null)
        {
            node = new Btnode();
            node.data = s;
            node.freq = 1;
            node.lc=null;
            node.rc=null;
            if(root==null)
            root = node;
        }
        else
        {
            if(s.compareToIgnoreCase(node.data)<0)
            node.lc = create(s,node.lc);
            else if(s.compareToIgnoreCase(node.data)>0)
            node.rc = create(s,node.rc);
            else
            node.freq++;
        }
        return node;
    }
    void inorder_printer(Btnode node)
    {
        if(node!=null)
        {
            inorder_printer(node.lc);
            System.out.println(node.data+" "+node.freq);
            inorder_printer(node.rc);
        }
    }
    int Number_Of_Nodes(Btnode node)
    {
        if(node!=null)
        return Number_Of_Nodes(node.lc)+Number_Of_Nodes(node.rc)+1;
        else
        return 0;
    }
    void populate(Btnode node,Btnode b[])
    {
        if(node!=null)
        {
            populate(node.lc,b);
            b[i++] = node;
            populate(node.rc,b);
        }
    }
}
public class Main
{
	public static void main(String[] args) throws IOException
	{
		Scanner sc = new Scanner(System.in);
		String str = sc.nextLine();
		String temp = "";
		BinaryTree bt = new BinaryTree();
        Btnode node = null;
		while(str!=null)
		{
		    try 
		    {
		        int index = str.indexOf(' ');
		        int g = str.length();
		        temp = str.substring(0,index);
		        temp = temp.replaceAll("[^a-zA-Z0-9]","");
		        temp = temp.toLowerCase();
		        str = str.substring(index+1,g);
		        node = bt.create(temp,node);
		    }
		    catch(Exception e)
		    {
		        str = str.replaceAll("[^a-zA-Z0-9]","");
		        str = str.toLowerCase();
		        node = bt.create(str,node);
		        break;
		    }
		}    
		int size = bt.Number_Of_Nodes(node);
		Btnode[] b = new Btnode[size];
		bt.populate(node,b);
		quicksort(b,0,size-1);
		for(int i=size-1;i>=max(0,size-5);i--)
		System.out.println(b[i].data+" "+b[i].freq);
	}
	static int max(int x,int y)
	{
	    if(x>y)
	    return x;
	    else
	    return y;
	}
	static void quicksort(Btnode b[],int x,int y)
	{
	    if(x<y)
        {
            int s = partition(b,x,y);
            if(x!=s-1)
            quicksort(b,x,s-1);
            if(s+1!=y)
            quicksort(b,s+1,y);
        }
	}
	static int partition(Btnode b[],int first,int last)
    {
        int x=first,y=last;
        int piv = b[y].freq;
        while(x!=y)
        {
            while(b[x].freq<piv&&x!=y)
            x++;
            while(b[y].freq>=piv&&y!=x)
            y--;
            if(x<y)
            {
                Btnode temp = b[x];
                b[x] = b[y];
                b[y] = temp;
            }
        }    
        if(x==y)
        {
            Btnode temp = b[last];
            b[last] = b[x];
            b[x] = temp;
        }
        return x;
    }
}
