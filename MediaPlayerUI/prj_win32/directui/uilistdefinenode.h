#ifndef UI_LIST_DEFINE_NODE_H
#define UI_LIST_DEFINE_NODE_H
#include <math.h>

namespace DirectUICore
{

struct NodeData
{
	int level_;
	bool folder_;
	bool child_visible_;
	bool old_child_visible_;
	bool has_child_;
	bool search_hide_;
	CStdString value;
	CListContainerElementUI* list_elment_;
};

double CalculateDelay( double state );

class DIRECTUI_API Node
{
public:
	Node();
	explicit Node( NodeData t );
	Node( NodeData t, Node* parent );
	~Node();
	NodeData& data();
	int num_children() const;
	Node* child( int i );
	Node* parent();
	bool folder() const;
	bool has_children() const;
	void add_child( Node* child );
	void add_child_at( int nIndex, Node* child );
	void remove_child( Node* child );
	void remove_child( int nStartIndex, int nEndIndex );
	Node* get_last_child();
	Node* operator [](int i){return child(i);}
private:
	void set_parent( Node* parent );

private:
	typedef std::vector<Node*>	Children;
	Children	children_;
	Node* parent_;
	NodeData data_;
};

} // DirectUICore

#endif // UI_LIST_DEFINE_NODE_H