#include<Windows.h>
#include"ChemistryDLL.h"

class CChemistry :public ISearch
{
private:
	long m_cRef;
public:
	CChemistry(void);
	~CChemistry(void);
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	HRESULT __stdcall ElementSearch(int);
};
class CChemistryClassFactory :public IClassFactory
{
private:
	long m_cRef;
public:
	CChemistryClassFactory(void);
	~CChemistryClassFactory(void);
	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);
	HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
	HRESULT __stdcall LockServer(BOOL);
};

long glNumberOfActiveComponents = 0;
long glNumberOfSeverLocks = 0;

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return (TRUE);
}

CChemistry::CChemistry(void)
{
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

CChemistry::~CChemistry(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}

HRESULT CChemistry::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISearch*>(this);
	else if (riid == IID_ISearch)
		*ppv = static_cast<ISearch*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CChemistry::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CChemistry::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT CChemistry::ElementSearch(int Num)
{
	char str[20];
	if (Num == 1)
	{
		MessageBox(NULL, TEXT(" ->Name:Hydrogen \n ->Number:1\n ->Group:1\n ->Period:1\n ->Formula:H\n ->Mass:1.01\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 2)
	{
		MessageBox(NULL, TEXT("Name:Helium | Number:2 | Group:18 | Period:1 | Formula:He | Mass:4.00"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 3)
	{
		MessageBox(NULL, TEXT("Name:Lithium | Number:3 | Group:1 | Period:2 | Formula:Li | Mass:6.94"), TEXT("Your Result is:"), MB_OK);
	}

	else if (Num == 4)
	{
		MessageBox(NULL, TEXT("Name:Beryllium | Number:4 | Group:2 | Period:2 | Formula:Be | Mass:9.01"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 5)
	{
		MessageBox(NULL, TEXT(" ->Name:Boron \n ->Number:5\n ->Group:13\n ->Period:2\n ->Formula:B\n ->Mass:10.81\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 6)
	{
		MessageBox(NULL, TEXT(" ->Name:Carbon \n ->Number:6\n ->Group:14\n ->Period:2\n ->Formula:C\n ->Mass:12.01\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 7)
	{
		MessageBox(NULL, TEXT(" ->Name:Nitrogen \n ->Number:7\n ->Group:15\n ->Period:2\n ->Formula:N\n ->Mass:14.01\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 8)
	{
		MessageBox(NULL, TEXT(" ->Name:Oxygen \n ->Number:8\n ->Group:16\n ->Period:2\n ->Formula:O\n ->Mass:16.00\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 9)
	{
		MessageBox(NULL, TEXT(" ->Name:Fluorine \n ->Number:9\n ->Group:17\n ->Period:2\n ->Formula:F\n ->Mass:19.00\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 10)
	{
		MessageBox(NULL, TEXT(" ->Name:Neon \n ->Number:10\n ->Group:18\n ->Period:2\n ->Formula:Ne\n ->Mass:20.18\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 11)
	{
		MessageBox(NULL, TEXT(" ->Name:Sodium \n ->Number:11\n ->Group:1\n ->Period:3\n ->Formula:Na\n ->Mass:22.99\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 12)
	{
		MessageBox(NULL, TEXT(" ->Name:Magnesium \n ->Number:12\n ->Group:2\n ->Period:3\n ->Formula:Mg\n ->Mass:24.31\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 13)
	{
		MessageBox(NULL, TEXT(" ->Name:Aluminum \n ->Number:13\n ->Group:13\n ->Period:3\n ->Formula:Al\n ->Mass:26.98\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 14)
	{
		MessageBox(NULL, TEXT(" ->Name:Silicon \n ->Number:14\n ->Group:14\n ->Period:3\n ->Formula:Si\n ->Mass:28.09\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 15)
	{
		MessageBox(NULL, TEXT(" ->Name:Phosphorus \n ->Number:15\n ->Group:15\n ->Period:3\n ->Formula:p\n ->Mass:30.97\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 16)
	{
		MessageBox(NULL, TEXT(" ->Name:sulfur \n ->Number:16\n ->Group:16\n ->Period:3\n ->Formula:S\n ->Mass:32.06\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 17)
	{
		MessageBox(NULL, TEXT(" ->Name:chlorine \n ->Number:17\n ->Group:17\n ->Period:3\n ->Formula:Cl\n ->Mass:35.45\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 18)
	{
		MessageBox(NULL, TEXT(" ->Name:argon \n ->Number:18\n ->Group:18\n ->Period:3\n ->Formula:Ar\n ->Mass:39.95\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 19)
	{
		MessageBox(NULL, TEXT(" ->Name:potassium \n ->Number:19\n ->Group:1\n ->Period:4\n ->Formula:K\n ->Mass:39.10\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 20)
	{
		MessageBox(NULL, TEXT(" ->Name:calcium \n ->Number:20\n ->Group:2\n ->Period:4\n ->Formula:Ca\n ->Mass:40.08\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 21)
	{
		MessageBox(NULL, TEXT(" ->Name:scandium \n ->Number:21\n ->Group:3\n ->Period:4\n ->Formula:Sc\n ->Mass:44.96\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 22)
	{
		MessageBox(NULL, TEXT(" ->Name:titanium \n ->Number:22\n ->Group:4\n ->Period:4\n ->Formula:Ti\n ->Mass:47.88\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 23)
	{
		MessageBox(NULL, TEXT(" ->Name:vanadium \n ->Number:23\n ->Group:5\n ->Period:4\n ->Formula:V\n ->Mass:50.94\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 24)
	{
		MessageBox(NULL, TEXT(" ->Name:chromium \n ->Number:24\n ->Group:6\n ->Period:4\n ->Formula:Cr\n ->Mass:52.00\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 25)
	{
		MessageBox(NULL, TEXT(" ->Name:manganese \n ->Number:25\n ->Group:7\n ->Period:4\n ->Formula:Mn\n ->Mass:54.94\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 26)
	{
		MessageBox(NULL, TEXT(" ->Name:iron \n ->Number:26\n ->Group:8\n ->Period:4\n ->Formula:Fe\n ->Mass:55.85\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 27)
	{
		MessageBox(NULL, TEXT(" ->Name:cobalt \n ->Number:27\n ->Group:9\n ->Period:4\n ->Formula:Co\n ->Mass:58.93\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 28)
	{
		MessageBox(NULL, TEXT(" ->Name:nickel \n ->Number:28\n ->Group:10\n ->Period:4\n ->Formula:Ni\n ->Mass:58.69\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 29)
	{
		MessageBox(NULL, TEXT(" ->Name:copper \n ->Number:29\n ->Group:11\n ->Period:4\n ->Formula:Cu\n ->Mass:63.55\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 30)
	{
		MessageBox(NULL, TEXT(" ->Name:zinc \n ->Number:30\n ->Group:12\n ->Period:4\n ->Formula:Zn\n ->Mass:65.38\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 31)
	{
		MessageBox(NULL, TEXT(" ->Name:gallium \n ->Number:31\n ->Group:13\n ->Period:4\n ->Formula:Ga\n ->Mass:69.72\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 32)
	{
		MessageBox(NULL, TEXT(" ->Name:germanium \n ->Number:32\n ->Group:14\n ->Period:4\n ->Formula:Ge\n ->Mass:72.61\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 33)
	{
		MessageBox(NULL, TEXT(" ->Name:arsonic \n ->Number:33\n ->Group:15\n ->Period:4\n ->Formula:As\n ->Mass:74.92\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 34)
	{
		MessageBox(NULL, TEXT(" ->Name:selenium \n ->Number:34\n ->Group:16\n ->Period:4\n ->Formula:Se\n ->Mass:78.96\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 35)
	{
		MessageBox(NULL, TEXT(" ->Name:bromine \n ->Number:35\n ->Group:17\n ->Period:4\n ->Formula:Br\n ->Mass:79.90\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 36)
	{
		MessageBox(NULL, TEXT(" ->Name:krypton \n ->Number:36\n ->Group:18\n ->Period:4\n ->Formula:Kr\n ->Mass:83.80\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 37)
	{
		MessageBox(NULL, TEXT(" ->Name:rubidium \n ->Number:37\n ->Group:1\n ->Period:5\n ->Formula:Rb\n ->Mass:85.47\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 38)
	{
		MessageBox(NULL, TEXT(" ->Name:stronthum \n ->Number:38\n ->Group:2\n ->Period:5\n ->Formula:Sr\n ->Mass:87.62\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 39)
	{
		MessageBox(NULL, TEXT(" ->Name:ythrium \n ->Number:39\n ->Group:3\n ->Period:5\n ->Formula:Y\n ->Mass:88.91\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 40)
	{
		MessageBox(NULL, TEXT(" ->Name:zirconium \n ->Number:40\n ->Group:4\n ->Period:5\n ->Formula:Zr\n ->Mass:91.22\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 41)
	{
		MessageBox(NULL, TEXT(" ->Name:niobium \n ->Number:41\n ->Group:5\n ->Period:5\n ->Formula:Nb\n ->Mass:92.91\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 42)
	{
		MessageBox(NULL, TEXT(" ->Name:molybdenum \n ->Number:42\n ->Group:6\n ->Period:5\n ->Formula:Mo\n ->Mass:95.94\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 43)
	{
		MessageBox(NULL, TEXT(" ->Name:techenium\n ->Number:43\n ->Group:7\n ->Period:5\n ->Formula:Tc\n ->Mass:98.91\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 44)
	{
		MessageBox(NULL, TEXT(" ->Name:ruthenium \n ->Number:44\n ->Group:8\n ->Period:5\n ->Formula:Ru\n ->Mass:101.07\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 45)
	{
		MessageBox(NULL, TEXT(" ->Name:rhodium \n ->Number:45\n ->Group:9\n ->Period:5\n ->Formula:Rh\n ->Mass:102.91\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 46)
	{
		MessageBox(NULL, TEXT(" ->Name:palladium \n ->Number:46\n ->Group:10\n ->Period:5\n ->Formula:Pd\n ->Mass:106.42\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 47)
	{
		MessageBox(NULL, TEXT(" ->Name:silver \n ->Number:47\n ->Group:11\n ->Period:5\n ->Formula:Ag\n ->Mass:107.87\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 48)
	{
		MessageBox(NULL, TEXT(" ->Name:cadmium \n ->Number:48\n ->Group:12\n ->Period:5\n ->Formula:Cd\n ->Mass:112.41\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 49)
	{
		MessageBox(NULL, TEXT(" ->Name:indium \n ->Number:49\n ->Group:13\n ->Period:5\n ->Formula:In\n ->Mass:114.82\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 50)
	{
		MessageBox(NULL, TEXT(" ->Name:tin \n ->Number:50\n ->Group:14\n ->Period:5\n ->Formula:Sn\n ->Mass:118.69\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 51)
	{
		MessageBox(NULL, TEXT(" ->Name:antimony \n ->Number:51\n ->Group:15\n ->Period:5\n ->Formula:Sb\n ->Mass:121.75\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 52)
	{
		MessageBox(NULL, TEXT(" ->Name:tellurium \n ->Number:52\n ->Group:16\n ->Period:5\n ->Formula:Te\n ->Mass:127.60\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 53)
	{
		MessageBox(NULL, TEXT(" ->Name:iodine \n ->Number:53\n ->Group:17\n ->Period:5\n ->Formula:I\n ->Mass:126.90\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 54)
	{
		MessageBox(NULL, TEXT(" ->Name:xenon \n ->Number:54\n ->Group:18\n ->Period:5\n ->Formula:Xe\n ->Mass:131.29\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 55)
	{
		MessageBox(NULL, TEXT(" ->Name:cosiumn \n ->Number:55\n ->Group:1\n ->Period:6\n ->Formula:Cs\n ->Mass:132.91\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 56)
	{
		MessageBox(NULL, TEXT(" ->Name:barium \n ->Number:56\n ->Group:2\n ->Period:6\n ->Formula:Ba\n ->Mass:137.33\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 57)
	{
		MessageBox(NULL, TEXT(" ->Name:lanthanum \n ->Number:57\n ->Group:3\n ->Period:6\n ->Formula:La\n ->Mass:138.91\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 58)
	{
		MessageBox(NULL, TEXT(" ->Name:cerium \n ->Number:58\n ->Group:5\n ->Period:6\n ->Formula:Ce\n ->Mass:140.12\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 59)
	{
		MessageBox(NULL, TEXT(" ->Name:pruseodymium \n ->Number:59\n ->Group:6\n ->Period:6\n ->Formula:Pr\n ->Mass:140.91\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 60)
	{
		MessageBox(NULL, TEXT(" ->Name:neodymium \n ->Number:60\n ->Group:7\n ->Period:6\n ->Formula:Nd\n ->Mass:144.24\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 61)
	{
		MessageBox(NULL, TEXT(" ->Name:promethium \n ->Number:61\n ->Group:8\n ->Period:6\n ->Formula:Pm\n ->Mass:145\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 62)
	{
		MessageBox(NULL, TEXT(" ->Name:samarium \n ->Number:62\n ->Group:9\n ->Period:6\n ->Formula:Sm\n ->Mass:150.40\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 63)
	{
		MessageBox(NULL, TEXT(" ->Name:europium \n ->Number:63\n ->Group:10\n ->Period:6\n ->Formula:Eu\n ->Mass:151.97\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 64)
	{
		MessageBox(NULL, TEXT(" ->Name:gadolinium \n ->Number:64\n ->Group:11\n ->Period:6\n ->Formula:Gd\n ->Mass:157.25\n"), TEXT("Your Result is:"), MB_OK);
	}

	else if (Num == 65)
	{
	MessageBox(NULL, TEXT(" ->Name:terbium \n ->Number:65\n ->Group:12\n ->Period:6\n ->Formula:Tb\n ->Mass:153.93\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 66)
	{
	MessageBox(NULL, TEXT(" ->Name:dysprosium \n ->Number:66\n ->Group:13\n ->Period:6\n ->Formula:Dy\n ->Mass:162.50\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 67)
	{
	MessageBox(NULL, TEXT(" ->Name:helmium \n ->Number:67\n ->Group:14\n ->Period:6\n ->Formula:Ho\n ->Mass:164.93\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 68)
	{
	MessageBox(NULL, TEXT(" ->Name:erbium \n ->Number:68\n ->Group:15\n ->Period:6\n ->Formula:Er\n ->Mass:167.26\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 69)
	{
	MessageBox(NULL, TEXT(" ->Name:thulium \n ->Number:69\n ->Group:16\n ->Period:6\n ->Formula:Tm\n ->Mass:168.94\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 70)
	{
	MessageBox(NULL, TEXT(" ->Name:ytlerhium \n ->Number:70\n ->Group:17\n ->Period:6\n ->Formula:Yb\n ->Mass:173.04\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 71)
	{
	MessageBox(NULL, TEXT(" ->Name:lutelium \n ->Number:71\n ->Group:18\n ->Period:6\n ->Formula:Lu\n ->Mass:174.97\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 72)
	{
	MessageBox(NULL, TEXT(" ->Name:hefnium \n ->Number:72\n ->Group:4\n ->Period:6\n ->Formula:Hf\n ->Mass:178.49\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 73)
	{
	MessageBox(NULL, TEXT(" ->Name:tantalum \n ->Number:73\n ->Group:5\n ->Period:6\n ->Formula:Ta\n ->Mass:180.95\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 74)
	{
	MessageBox(NULL, TEXT(" ->Name:wolfrum \n ->Number:74\n ->Group:6\n ->Period:6\n ->Formula:W\n ->Mass:183.85\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == '75') 
	{
	MessageBox(NULL, TEXT(" ->Name:rhenium \n ->Number:75\n ->Group:7\n ->Period:6\n ->Formula:Re\n ->Mass:186.21\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 76)
	{
	MessageBox(NULL, TEXT(" ->Name:osmium \n ->Number:76\n ->Group:8\n ->Period:6\n ->Formula:Os\n ->Mass:190.2\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 77)
	{
	MessageBox(NULL, TEXT(" ->Name:iridium \n ->Number:77\n ->Group:9\n ->Period:6\n ->Formula:Ir\n ->Mass:192.22\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 78)
	{
	MessageBox(NULL, TEXT(" ->Name:platinum \n ->Number:78\n ->Group:10\n ->Period:6\n ->Formula:Pt\n ->Mass:195.08\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 79)
	{
	MessageBox(NULL, TEXT(" ->Name:gold \n ->Number:79\n ->Group:11\n ->Period:6\n ->Formula:Au\n ->Mass:196.97\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 80)
	{
	MessageBox(NULL, TEXT(" ->Name:mercury \n ->Number:80\n ->Group:12\n ->Period:6\n ->Formula:Hg\n ->Mass:200.59\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 81)
	{
	MessageBox(NULL, TEXT(" ->Name:thallium \n ->Number:81\n ->Group:13\n ->Period:6\n ->Formula:Tl\n ->Mass:204.38\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 82)
	{
	MessageBox(NULL, TEXT(" ->Name:lead \n ->Number:82\n ->Group:14\n ->Period:6\n ->Formula:Pb\n ->Mass:207.20\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 83) 
	{
	MessageBox(NULL, TEXT(" ->Name:bismuth \n ->Number:83\n ->Group:15\n ->Period:6\n ->Formula:Bi\n ->Mass:208.98\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 84)
	{  
	MessageBox(NULL, TEXT(" ->Name:polonium \n ->Number:84\n ->Group:16\n ->Period:6\n ->Formula:Po\n ->Mass:209\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 85)
	{  
	MessageBox(NULL, TEXT(" ->Name:asiatine \n ->Number:85\n ->Group:17\n ->Period:6\n ->Formula:At\n ->Mass:210\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 86)
	{
	MessageBox(NULL, TEXT(" ->Name:radon \n ->Number:86\n ->Group:18\n ->Period:6\n ->Formula:Rn\n ->Mass:222\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 87)
	{  
	MessageBox(NULL, TEXT(" ->Name:fruncium \n ->Number:87\n ->Group:1\n ->Period:7\n ->Formula:Fr\n ->Mass:223\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 88)
	{   
	MessageBox(NULL, TEXT(" ->Name:radium \n ->Number:88\n ->Group:2\n ->Period:7\n ->Formula:Ra\n ->Mass:226.03\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 89) 
	{ 
	MessageBox(NULL, TEXT(" ->Name:actinium \n ->Number:89\n ->Group:3\n ->Period:7\n ->Formula:Ac\n ->Mass:277.03\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 90)
	{   
	MessageBox(NULL, TEXT(" ->Name:thorium \n ->Number:90\n ->Group:5\n ->Period:7\n ->Formula:Th\n ->Mass:232.04\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 91)
	{
	MessageBox(NULL, TEXT(" ->Name:protactinium \n ->Number:91\n ->Group:6\n ->Period:7\n ->Formula:Pa\n ->Mass:231.04\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 92)
	{
	MessageBox(NULL, TEXT(" ->Name:Uranium \n ->Number:92\n ->Group:7\n ->Period:7\n ->Formula:U\n ->Mass:238.03\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 93) 
	{  
	MessageBox(NULL, TEXT(" ->Name:Neptunium \n ->Number:93\n ->Group:8\n ->Period:7\n ->Formula:No\n ->Mass:237.05\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 94) 
	{
	MessageBox(NULL, TEXT(" ->Name:Plutonium \n ->Number:94\n ->Group:9\n ->Period:7\n ->Formula:Pu\n ->Mass:244\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 95) 
	{
	MessageBox(NULL, TEXT(" ->Name:americium \n ->Number:95\n ->Group:10\n ->Period:7\n ->Formula:Am\n ->Mass:244\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 96) 
	{
	MessageBox(NULL, TEXT(" ->Name:curium \n ->Number:96\n ->Group:11\n ->Period:7\n ->Formula:Cm\n ->Mass:247\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 97)
	{  
	MessageBox(NULL, TEXT(" ->Name:borkelium \n ->Number:97\n ->Group:12\n ->Period:7\n ->Formula:Bk\n ->Mass:247\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 98)
	{ 
	MessageBox(NULL, TEXT(" ->Name:californium \n ->Number:98\n ->Group:13\n ->Period:7\n ->Formula:Cf\n ->Mass:251\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 99)
	{  
	MessageBox(NULL, TEXT(" ->Name:einsteinium \n ->Number:99\n ->Group:14\n ->Period:7\n ->Formula:Es\n ->Mass:252\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 100)
	{
	MessageBox(NULL, TEXT(" ->Name:formium \n ->Number:100\n ->Group:15\n ->Period:7\n ->Formula:Fm\n ->Mass:257\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 101)
	{
	MessageBox(NULL, TEXT(" ->Name:mendelevium \n ->Number:101\n ->Group:16\n ->Period:7\n ->Formula:Md\n ->Mass:258\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 102)
	{
	MessageBox(NULL, TEXT(" ->Name:nebelium \n ->Number:102\n ->Group:17\n ->Period:7\n ->Formula:No\n ->Mass:259\n"), TEXT("Your Result is:"), MB_OK);
	}
	else if (Num == 103)
	{
	MessageBox(NULL, TEXT(" ->Name:lawrencium \n ->Number:103\n ->Group:18\n ->Period:7\n ->Formula:Lr\n ->Mass:260\n"), TEXT("Your Result is:"), MB_OK);
	}
	return(S_OK);
}

CChemistryClassFactory::CChemistryClassFactory(void)
{
	m_cRef = 1;
}

CChemistryClassFactory::~CChemistryClassFactory(void)
{

}

HRESULT CChemistryClassFactory::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory*>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory*>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CChemistryClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CChemistryClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT CChemistryClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	CChemistry *pCChemistry = NULL;
	HRESULT hr;
	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);
	pCChemistry = new CChemistry;
	if (pCChemistry == NULL)
		return(E_OUTOFMEMORY);
	hr = pCChemistry->QueryInterface(riid, ppv);
	pCChemistry->Release();
	return(hr);
}

HRESULT CChemistryClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfSeverLocks);
	else
		InterlockedDecrement(&glNumberOfSeverLocks);
	return(S_OK);
}


HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	CChemistryClassFactory *pCChemistryClassFactory = NULL;
	HRESULT hr;
	if (rclsid != CLSID_Chemistry)
		return(CLASS_E_CLASSNOTAVAILABLE);
	pCChemistryClassFactory = new CChemistryClassFactory;
	if (pCChemistryClassFactory == NULL)
		return(E_OUTOFMEMORY);
	hr = pCChemistryClassFactory->QueryInterface(riid, ppv);
	pCChemistryClassFactory->Release();
	return(hr);
}
HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (&glNumberOfSeverLocks == 0))
		return(S_OK);
	else
		return(S_FALSE);
}
