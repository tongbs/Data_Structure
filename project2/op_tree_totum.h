#include<iostream>
using namespace std;

class node{
public:
	node();
	node(int value);
	~node();
	friend void gothrough(node *p);

private:
	node *left, *right; // the left child and the right child pointer
	int number; // record the node's number
	int is_threadl, is_threadr; //the flag to record whether the pointer is a thread or not

	friend class op_tree_totum;//you could access all valuables in class op_tree_totum
};

//ctor
node::node(){
	left = right = NULL;
	is_threadl = 1;
	is_threadr = 1;
}

//ctor
node::node(int value){
	number = value;
	left = right = NULL;
	is_threadl = 1;
	is_threadr = 1;
}

//dtor
node::~node(){

}

class op_tree_totum{

public:
	op_tree_totum();
	~op_tree_totum();
	void insertion(int s);
	void deletion(int s);
	void inorder_run();
	void reverseorder_run();
	int size();

private:
	node *root, *head, *tail;
	int num;//caculate how many nodes in the totum
};

//ctor
op_tree_totum::op_tree_totum(){
	head = new node();
	tail = new node();
	head->right = tail; //initialize the head node to connect to the tail node
	tail->left = head;
	root = NULL;
	num = 0;
}

//dtor
op_tree_totum::~op_tree_totum(){
	node *p = root;
	if(p!=NULL)	gothrough(p);
	num = 0;
	if (head != NULL)delete head;
	if (tail != NULL)delete tail;
}

void gothrough(node *p){
	if (p->is_threadl==0 && p->left!= NULL) gothrough(p->left);
	if (p->is_threadr==0 && p->right!= NULL) gothrough(p->right);
	delete p;
}

void op_tree_totum::insertion(int s){//insertion
	
	node *p = new node(s);
	node *temp;
	//Start from root left 
		if(root == NULL){
			root = new node();
			root->number = 99000;
			root->right = root;//root right node接到自己 
			root->left = p;
			p->left = root;
			p->right = root;
			head->left = p;
			tail->right = p;
			num++;
	}//TODO: fill in the code to do the insertion of the node with number s
	
	else {//從root-left開始走 比插入的點大往左 反之往右 
		temp=root->left;
		while(s!=temp->number){
			if(s < temp->number){
				if(temp->is_threadl) 
					break;
				else temp = temp->left;
			}
			else {//left_subtree 最底節點thread是1 
				if(temp->is_threadr) 
					break;
				else temp = temp->right;
			}
		}//find parent
		
		if(s < temp->number){  //判斷插入的點和parents的關係 
			p->left = temp->left;
			p->right = temp;
			temp->left = p;
			temp->is_threadl = 0;
			if(p->left == root) head->left = p;
			num++;
		}
		else {           //if 接在右邊 進行thread換 
			p->right = temp->right;
			p->left = temp;
			temp->right = p;
			temp->is_threadr = 0;
			if(p->right == root) {
				tail->right=p;}
			num++;
		}
	}


}

void op_tree_totum::deletion(int s){
	//TODO: fill in the code to do the deletion of the node with number s
	node *p = root->left ,*p_parent = root;
	
	
	//find s 找要刪除的點 
	while(p->number != s){
		if(s < p->number) {
			if(p->is_threadl) 
				return;        //假如都沒有找到則return 
			p_parent = p ;
			p = p->left;
			
		}
		else if(s > p->number) {
			if(p->is_threadr) 
				return;
			p_parent = p ; 
			p = p->right;
		}	
	}
	
	
	node *orin =p;
	if(!p->is_threadl && !p->is_threadr){    //欲刪除的點兩邊都有節點 
		
		p_parent = p;
		p = p->left;
		while(!p->is_threadr) {
			p_parent = p;
			p= p->right;
		}
		
		orin->number = p->number;     //把欲刪除的點和左子數最大的點交換 
    }
	 
	node *target = p;
	if(p_parent->number >= target->number)   //處理parent left-subtree 
    {
        if(target->is_threadr && target->is_threadl)
        {                                           
            p_parent->left=target->left;                 
            p_parent->is_threadl=1;                      
            if(target->left==root) head->left=p_parent;  
        }
        else if(target->is_threadr)//target 有Left_child                 
        {                                           
            node* largest = target->left;           
            while(!largest->is_threadr)             
                largest=largest->right;             
            largest->right=target->right;           
            p_parent->left=target->left;
            if(target->right==root) tail->right=largest; 
        }
        else                                        
        {             //target右邊有小孩                                       
            node* smallest = target->right;         
            while(!smallest->is_threadl){
			    smallest=smallest->left;}            
            smallest->left=target->left;            
            p_parent->left=target->right;
            if(target->left==root){
				head->left=smallest;} 
        }
    }
    else                 //在parent右邊 
    {
        if(target->is_threadr && target->is_threadl)      //target no children
        {                                               
            p_parent->right=target->right;                   
            p_parent->is_threadr=1;                          
            if(target->right==root){
		 		tail->right=p_parent;
			}
        }
        else if(target->is_threadr)    //target has left subtree                   
        {                                               
            node* largest = target->left;               
            while(!largest->is_threadr){       //找左子數最大的數 
			    largest=largest->right;
			}                 
            largest->right=target->right;               
            p_parent->right=target->left;
            if(target->right==root){
			 	tail->right=largest;
			}
        }
        else                                            
        {   //右邊有小孩                                            
            node* smallest = target->right;             
            while(!smallest->is_threadl){    //找右子數小孩最小的 
            	smallest=smallest->left; 
			}
            smallest->left=target->left;                
            p_parent->right=target->right;
            if(target->left==root) 
				head->left=smallest; 
        }
    }
	delete p;              //上述判斷完成後刪除p 
	num--;
	
}

void op_tree_totum::inorder_run(){
	//TODO: travel the tree from the head node to the tail node and output the values
	//You should NOT use stack or recurtion 
	node *current;
	current = head->left;
	
	while(current!=root){
		
		cout<< current->number<<" ";
		node *tmp = current->right;
		if(!current->is_threadr){
			while(!tmp->is_threadl) 
				tmp = tmp->left;//find 右子樹最左的點 
		} 
		current = tmp;
		
		
	}
	cout<<endl;
}

void op_tree_totum::reverseorder_run(){
	//TODO: travel the tree from the tail node to the head node and output the values
	//You should NOT use stack or recurtion 
	node *current;
	current = tail->right;  //倒過來 
	
	while(current!=root){
		
		cout<< current->number<<" ";
		node *tmp = current->left;
		if(!current->is_threadl){
			while(!tmp->is_threadr) 
				tmp = tmp->right;
		} 
		current = tmp;
		
		
	}
	cout<<endl;

}

int op_tree_totum::size(){
	return num;
}

