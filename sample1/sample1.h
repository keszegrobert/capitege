class C{
	int m_tag;
public:
	C():m_tag(-1){}
	~C(){m_tag=-1;}
	void SetTag(int t){m_tag = t;}
	int GetTag(){return m_tag;}
};