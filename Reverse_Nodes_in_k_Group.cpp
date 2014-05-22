/*
 *	Use stack to implement the reverse order of linked list
 *
 *	Andy Liu 	May 22th,2014
 *
 *
 * */
#include <iostream>
#include <stack>
#include <ctime>
using namespace std;

struct ListNode{
	int val;
	ListNode* next;
	ListNode(int x):val(x),next(NULL){}
};


ListNode* reverseKGroup(ListNode* head,int k) 
{
	if(k == 1)
		return head;
	stack<ListNode*> s;
	bool isHead = true;
	ListNode *listhead = head,*cur = head,*backup, *newcur;
	while(cur != NULL)
	{
		int count = k;
		while(cur != NULL && count > 0)
		{
			if(count == k)
				backup = cur;
				s.push(cur);
				cur = cur->next;
				count --;	
		}
		if(count == 0)
		{
			while(!s.empty())
			{
				if(isHead)
				{
					listhead = newcur = s.top();
					s.pop();
					isHead = false;
				}
				else
				{
					ListNode* tmp = s.top();
					s.pop();
					// insert
					tmp->next = newcur->next;
					newcur->next = tmp;
					newcur = newcur->next;
				}
			}
	}
		else // count != 0
		{
			cur = backup;
			while (cur != NULL)
			{
				ListNode* tmp = cur->next;// temperorily stored
				cur->next = newcur->next; // insert cur after newcur
				newcur->next = cur;
				newcur = newcur->next; // cur
				//cur = cur->next; //不再是之前那个cur->next
				cur = tmp;
			}
		}
	}
	//complete the process,set end == NULL
	newcur->next = NULL;			
	return listhead;
}
/**
 *
 *
 *	another version from :http://blog.csdn.net/kenden23/article/details/18770889

class Solution125 {
public:
    ListNode *reverseKGroup(ListNode *head, int k) 
    {
	    ListNode dummy(0);
	    dummy.next = head;
	    ListNode *pre = &dummy;
	    while (head)
	    {
		    int i = 1;
		    for ( ; i < k && head->next; i++)//容易错误处
		    {
			    head = head->next;
		    }
		    if (i == k)
		    {
			    ListNode *last = pre->next;//容易遗漏处
			    head = pre->next->next;
			    for (i = 1; i < k; i++)
			    {
				    ListNode *t = head->next;
				    head->next = pre->next;
				    pre->next = head;
				    head = t;
			    }
			    pre = last;//容易遗漏处
			    last->next = head;//容易遗漏处
		    }
		    else break;//容易遗漏处
	    }
	    return dummy.next;
    }
};
 *
 *
 *
 *
 *
 * */

int main()
{
	int n,num,k;
	cout<<"enter the length of linklist:"<<endl;
	cin>>n;
	ListNode* cur ;
	ListNode* listhead;
	bool firstElem = true;
	while(n)
	{
		cin>>num;
		if(firstElem)
		{
			cur = new ListNode(num);
			listhead = cur;
			--n;
			firstElem = false;
		}	
		else 
		{
			ListNode* p = new ListNode(num);
			p->next = cur->next;//插入节点要两步！
			cur->next = p;
			cur = cur->next;
			--n;
		}	
	}
	cout<<"original order:"<<endl;
	cur = listhead;
	while(cur != NULL)
	{
		cout<<cur->val<<" ";
		cur = cur->next;
	}
	cout<<endl;
	cout<<"enter k:"<<endl;
	cin>>k;
	time_t tbeg = time(NULL);
	cur = reverseKGroup(listhead,k);
	time_t tend = time(NULL);
	cout<<"time spent:"<<(tend-tbeg)*1000/CLOCKS_PER_SEC<<endl;
	cout<<"after reverseKGroup:"<<endl;
	while(cur != NULL)
	{
		cout<<cur->val<<" ";
		cur = cur->next;
	}
	cout<<endl;
	return 0;
}
