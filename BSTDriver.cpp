#include "wx/wx.h"
#include "wx/sizer.h"

#include "DrawPanel.h"
#include "ImageLoader.h"


#include "Circle.h"
#include "Line.h"
#include "AVLTree.h"
#include "ListArray.h"
#include "CD.h"
#include "BinarySearchTree.h"
using namespace CSC2110;
#include <iostream>
using namespace std;
class MyApp: public wxApp
{
    bool OnInit();
 
    wxFrame* frame;
    DrawPanel* drawPane;
public:
 
};
 
IMPLEMENT_APP(MyApp)
 
bool MyApp::OnInit()
{
  // ListArray<CD>* cds = CD::readCDs("cds.txt");
    ListArray<CD>* cds = CD::readCDs("test.txt");
   int num_items = cds->size();
   cout << num_items << endl;

   ListArrayIterator<CD>* iter = cds->iterator();
   BinarySearchTree<CD>* bst = new BinarySearchTree<CD>(&CD::compare_items, &CD::compare_keys);
   while(iter->hasNext())
   {
      CD* cd = iter->next();
      bst->insert(cd);
   }
   delete iter;

   
   //DO THIS
   //test your tree sort method
   CD** unsorted_cds = cds->toArray();
   CD** sorted_cds = bst->treeSort(unsorted_cds, num_items, &CD::compare_items, &CD::compare_keys);
   
   for(int i = 0; i < num_items; i ++)
   {
	   sorted_cds[i]->getKey()->displayString();
	   cout<<endl;
   }
   delete[] unsorted_cds;
   delete[] sorted_cds;
   delete cds;
	String* remove_title = new String("Construct");
	bst->remove(remove_title);
	delete remove_title;
	cout<<"Right before the iterator"<<endl;
	BinaryTreeIterator<CD>* iter2 = bst->iterator();
	cout<<"Iterator was created correctly"<<endl;
	int counter = 1;
	iter2->setPreorder();
	cout<<iter2->hasNext();
	while(iter2->hasNext())
	{
		cout<<counter<<endl;
		CD* cd = iter2->next();
		cd->getKey()->displayString();
	}
   delete iter2;
   
   
	/*remove_title = new String("Construct");
	bst->remove(remove_title);
	delete remove_title;*/
   wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
   frame = new wxFrame((wxFrame *)NULL, -1,  wxT("BST Tree"), wxPoint(500,500), wxSize(1100,600));

   drawPane = new DrawPanel((wxFrame*) frame, bst);

   sizer->Add(drawPane, 1, wxEXPAND);

   frame->SetSizer(sizer);
   frame->SetAutoLayout(true);

   frame->Show();
   return true;
}
