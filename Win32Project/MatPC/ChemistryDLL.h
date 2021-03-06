class ISearch :public IUnknown
{
public:
	virtual HRESULT __stdcall ElementSearch(int) = 0;
};

const CLSID CLSID_Chemistry = { 0xf3048b, 0xde1d, 0x4ae7, 0xbe, 0x6e, 0x73, 0x5c, 0x46, 0x88, 0x72, 0x3 };
/*
// {00F3048B-DE1D-4AE7-BE6E-735C46887203}
IMPLEMENT_OLECREATE(<<class>>, <<external_name>>,
0xf3048b, 0xde1d, 0x4ae7, 0xbe, 0x6e, 0x73, 0x5c, 0x46, 0x88, 0x72, 0x3);
*/
const IID IID_ISearch = { 0xddde4a5c, 0xf34e, 0x476f, 0x99, 0x1d, 0x28, 0xfc, 0x5a, 0x3f, 0x8a, 0x2 };
/*
// {DDDE4A5C-F34E-476F-991D-28FC5A3F8A02}
IMPLEMENT_OLECREATE(<<class>>, <<external_name>>,
0xddde4a5c, 0xf34e, 0x476f, 0x99, 0x1d, 0x28, 0xfc, 0x5a, 0x3f, 0x8a, 0x2);

*/


