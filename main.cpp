#include <stdlib.h>
#include <iostream>
#include <memory>



using namespace std;

template <typename T>
struct Node       {
    
    T Value;
    weak_ptr<Node<T>> prev;
    shared_ptr<Node<T>> next;
    
    Node (T value){
        Value = value;
    }
    
    ~Node() {
        cout<<"Node destructor"<<endl;
    }
    
 };



template<typename T>
class List 
{public:  
     
     shared_ptr<Node<T>> start;
     weak_ptr<Node<T>> end;
     int size;
     
 public:
     List(): size(0){};
     ~List();
    
     void addNode (T value);
     void deleteNode (int i);
     void reverse ();
     void append (List<T>* a);

     List<T>* filter (bool (pred) (T));
     T* element(int i);
     

    
 };

template <typename T>
class Iterator {
public:
    Node<T>* result;
    bool dir;
    
public:
    
    Iterator(): result(nullptr){};
    
    Iterator(List<T>* ll, bool a){
        if (a==true){
            result = ll->start.get();
        }
        else {
            auto s = ll->end.lock();
            result = s.get();
        }
        dir = a;
    }
    
    ~Iterator(){
        result = nullptr;
    }
    
    void next (){
        if (dir==true && result != nullptr){
            result = result->next.get();
        }
        else if (dir==false && result != nullptr){
            auto s = result->prev.lock();
            result = s.get();
        }
        
        return;
    }

};

template <typename T> List<T>::~List() 
 {   
     cout<<"List destructor"<<endl;
     while(start){
       start = start->next;
     }
 }
 
/*template <typename T> void List<T>::addNode(T value){
    Node<T>* nd = new Node<T>;
    
    if (size==0){
        start.reset(nd);
        start->Value = value;
        end = start;
        
    }
    
    else{
        auto sp = end.lock();
        auto sp2 = end.lock();
        sp->next.reset(nd);
        sp.reset(sp->next.get());
        sp->prev = sp2;
        sp->Value = value;
        cout<<"Value size is "<<size<<" "<<sp->Value<<endl;
        end = sp;
        
    }
    
    size++;
    return;
}*/

template <typename T> 
void List<T>::addNode(T value){
    auto nd = make_shared<Node<T>>(value);
    
    if (size++ == 0){
        start = nd;
    } 
    else{
        auto sp = end.lock();
        sp->next = nd;
        nd->prev = sp;
    }

    end = nd;
}

template <typename T>
void List<T>::deleteNode(int i){
    
    if (i==0 || i>size){
        return;
    }
    else if (i==1){
        start = start->next;
        //start->prev = nullptr;
        }
    else if (i==size){
        auto sp = end.lock();
        auto sp2 = sp->prev.lock();
        sp2->next.reset();
        end = sp2;
    }
    else{
        shared_ptr<Node<T>> sp = start;

        for (int a=1; a<i; a++){
            sp = sp->next;
        }
        auto sprev = sp->prev.lock();
        sprev->next = sp->next;
        sp->next->prev = sprev;
    }
    
    
    size--;
    return;
    
}


template <typename T>
void List<T>::reverse(){
    shared_ptr<Node<T>> cur, s1, s2, d;
    cur = start;
    cout<<" start "<<start<<endl;
    for (int i=1; i<=size; i++){
        if (i==1){
            s1 = cur->next;
            cur->prev = s1;
            cur->next = nullptr;
            cout<<i<<" cur->next "<<s1<<endl;
            cout<<i<<" cur->prev.lock() "<<s2<<endl;
            cout<<" cur->next "<<cur->next<<endl;
            auto ss = cur->prev.lock();
            cout<<" cur->prev "<<ss<<endl;

            cur = s1;
            cout<<" cur "<<cur<<endl;

            
        }
        else{
            s1 = cur->next;
            s2 = cur->prev.lock();
            cur->next = s2;
            cur->prev = s1;
            cout<<i<<" cur->next "<<s1<<endl;
            cout<<i<<" cur->prev.lock() "<<s2<<endl;
            cout<<" cur->next "<<cur->next<<endl;
            auto ss = cur->prev.lock();
            cout<<" cur->prev "<<ss<<endl;
            
            d = cur;
            cur = s1;
            cout<<" cur "<<cur<<endl;

            
            }
           
        }
    
      
      s1 = start;
      s2 = end.lock();
      start = s2;
      end = s1;
      
      
      return;  

}

template <typename T>
    void List<T>::append(List<T>* a){
        auto s = end.lock();
        auto s1 = s->next;
        a->start->prev = s;
        s->next = a->start;
        auto e = a->end.lock();
        end = e;
        
        size+=a->size;
        return;
    }

template <typename T>
    T* List<T>::element(int i){
    Node<T>* ita;
    ita = start.get();
    
    if (i==0 || i>size) return NULL;
    
    for (int a=1; a<=i; a++){
        if (a==1) continue;
        else ita=ita->next.get();
    }
    return &(ita->Value);
}


template<typename T>
    List<T>* List<T>::filter (bool (pred) (T)){
        List<T>* ll = new List<T>;
        auto s = start;
        
        for (int i=1; i<=size; i++){
            if (pred (s->Value)){
                ll->addNode(s->Value);
            }
            s = s->next;
        }
        
        return ll;
    }

bool SaintP (string ex) {
    if (ex == "Saint P") return true;
    else return false;
    
}
    
    
int main ()
{
 system("CLS");
 
  string a;
  string b;
  string c;
  string d;
  
  a = "1 test";
  b = "2 test";
  c = "3 test";
  d = "4 test";
  
  
  List<string> ls;
  ls.addNode(a);
  cout<<"here will be size: "<<ls.size<<endl;
  ls.addNode(b);
  ls.addNode(c);
  ls.addNode(d);
  
  /*cout<<"VALUE:   "<<ls.start->Value<<endl;
  cout<<"size:   "<<ls.size<<endl;
  cout<<"2 test: "<<*(ls.element(2))<<endl;*/
  
  /*List<string> lsd;
  lsd.addNode(b);
  lsd.addNode(a);
  
  ls.append(&lsd);
  auto p = ls.end.lock();
  cout<<"1 test "<<p->Value<<endl;*/

  
  /*ls.deleteNode(2);
  cout<<"3 test: "<<*(ls.element(2))<<endl;
  cout<<"size is: "<<ls.size<<endl;*/
  
  /*ls.reverse();
  cout<<"Test 4: "<<ls.start->Value<<endl;
  cout<<"test 1: "<<ls.start->next->next->next->Value<<endl;
  cout<<"test 3: "<<ls.start->next->Value<<endl;
  cout<<"test 2: "<<ls.start->next->next->Value<<endl;
  auto dd = ls.end.lock();
  cout<<"end test1 "<<dd->Value<<endl;*/
  
  /*auto ita = Iterator<string>(&ls, true);
  cout<< "result test 1 "<< ita.result->Value<<endl;
  ita.next();
  cout<< "result test 2 "<< ita.result->Value<<endl;
  auto rev = Iterator<string>(&ls, 0);
  cout<< "result test 4 "<< rev.result->Value<<endl;
  ita.next();
  cout<< "result test 3 "<< rev.result->Value<<endl;*/
  
  ls.addNode("Saint P");
  auto l1 = ls.filter(SaintP);
  cout<<"SAINT P "<<l1->start->Value<<endl;


  //List<int> ls2;
  //ls2.addNode(1);
  //ls2.addNode(2);
  //auto l2 = ls2.filter(SaintP);
  
 
  
  
  

  return 0;
  
}