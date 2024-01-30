#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>


//Ham thay đoi mau
void DoiMau(int MauNen, int MauChu){
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); //Đau ra
    int Mau = MauNen * 16 + MauChu; //Cong thuc tao mau
    SetConsoleTextAttribute(hStdout, Mau); //Ham thay đoi mau
}
//Ham di chuyển con tro
void GoTo(SHORT X, SHORT Y){
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); //Đau ra
    COORD ToaDo; //Tao toa đo
    ToaDo.X = X;
    ToaDo.Y = Y;
	SetConsoleCursorPosition(hStdout, ToaDo); //Ham di chuyen
}
//Ham an con tro
void ShowCur(bool CursorVisibility){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;
    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = CursorVisibility;
    SetConsoleCursorInfo(handle, &ConCurInf);
}
//Ham lay toa đo x cua con tro
int where_x(){
	CONSOLE_SCREEN_BUFFER_INFO coninfo; 
	GetConsoleScreenBufferInfo (GetStdHandle(STD_OUTPUT_HANDLE), &coninfo); //Truyen vao đau ra va toa đo 
	return coninfo.dwCursorPosition.X; //Toa đo x cua con tro
}
//Ham lay toa đo y cua con tro
int where_y(){
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	GetConsoleScreenBufferInfo (GetStdHandle(STD_OUTPUT_HANDLE), &coninfo); //Truyen vao đau ra va toa đo
	return coninfo.dwCursorPosition.Y; //Toa đo y cua con tro
}

//In nhan vat
void NV(int x, int y){
	DoiMau(0,9);
	//Chan
	GoTo(x, y);
	printf("%c",19);
	//Đau
	GoTo(x, y-1);
	printf("%c",64);
	DoiMau(0,11);
}
//Xoa nhan vat
void XNV(int x, int y){
	//Chan 
	GoTo(x, y);
	printf(" ");
	//Đau
	GoTo(x, y-1);
	printf(" ");
}
//Ghi toa đo map
void GhiTD(){
	Map[DM].VT.x=where_x()-1;
    Map[DM].VT.y=where_y();
    Map[DM].kt=1;
    DM++;
}

void KTTN(int &x, int &y){
	KTKhoiDat(x,y);
	KTCongTac(x,y);
	KTDC(x,y);
	KTChiaKhoa(x,y);
	KTCua(x,y);
}
//Ham kiem tra vat can theo chieu ngan
int KTNgang(int x, int y){
	for(int i=0; i<1610; i++){
		//Xet chan
		if(x==Map[i].VT.x && y==Map[i].VT.y){
			if(Map[i].kt==1)
				return 1;
		}
		//Xet dau
		else if(x==Map[i].VT.x && y-1==Map[i].VT.y){
			if(Map[i].kt==1)
				return 1;
		}
	}
	return 0;
}
//Ham kiem tra vat can theo chieu doc
int KTDoc(int x, int y){
	for(int i=0; i<1610; i++){
		//Xet chan
		if(x==Map[i].VT.x && y==Map[i].VT.y){
			if(Map[i].kt==1){
				hR=1;
				return 1;
			}
		}
		//Xet dau
		else if(x==Map[i].VT.x && y-1==Map[i].VT.y){
			if(Map[i].kt==1){
				hR=1;
				return -1;
			}
		}
	}
	//Kiem tra xem co dung tren khoi dat khong
	for(int j=0; j<=DemKD; j++){
		if(x==KhoiDat[j].x && y==KhoiDat[j].y){
			hR=1;
			return 1;
		}
	}
	return 0;
}
//Ham roi tu do
void RoiTD(int &x, int &y){
	int xC=x, yC=y;
	while(1){
		y++;
		if(KTDoc(x,y)==0){
			Sleep(20);
			XNV(xC,yC);
			Sleep(20);
			NV(x,y);
			xC=x; yC=y;
		}
		else{
			y--;
			Sleep(20);
			NV(x,y);
			xC=x; yC=y;
			break;
		} 
	}
}
//Ham kiem tra dieu kien di chuyen cua nhan vat
void KTDC(int &x, int &y){
	if(KTNgang(x,y)==1){
		if(hD==1){
			x--;
		}
		else if(hD==-1){
			x++;
		}
	}
	if(KTDoc(x,y)==1){
		y--;
	}
	else if(KTDoc(x,y)==-1){
		y++;
	}
}

//Ham kiem tra cong tac
void KTCongTac(int x, int y){
	for(int i=0; i<=DemCT; i++){
		if(x==CTac[i].x && y==CTac[i].y){
			for(int j=0; j<=DemCC; j++){
				if(CuaChan[j].kt==i){
					GoTo(CuaChan[j].VT.x,CuaChan[j].VT.y);
					printf(" ");
					for(int h=0; h<=DM; h++){
						if(Map[h].VT.x==CuaChan[j].VT.x && Map[h].VT.y==CuaChan[j].VT.y){
							Map[h].kt=0;
						}
					}
				}
			}
		}
	}
}
//Ham kiem tra gai
void KTGai(int &x, int &y){
	for(int i=0; i<=DemGai; i++){
		//Neu trung gai thi tru HP va quay lai vi tri quy dinh 
		if((x==Gai[i].VT.x && y==Gai[i].VT.y) || (x==Gai[i].VT.x && y-1==Gai[i].VT.y)){
			HP--;
			NV(GaiQL[Gai[i].kt].x,GaiQL[Gai[i].kt].y);
			XNV(Gai[i].VT.x,Gai[i].VT.y);
			GoTo(Gai[i].VT.x,Gai[i].VT.y);
			DoiMau(0,9);
			printf("%c",30);
			DoiMau(0,11);
			x=GaiQL[Gai[i].kt].x; y=GaiQL[Gai[i].kt].y; //Quay lai vi tri quy dinh khi tao gai
		}
	}
}
// Ham kiem tra chia khoa
void KTChiaKhoa(int x, int y){
	for(int i=0; i<3; i++){
		//Neu trung chia khoa thi tang so luong chia khoa va duoi toa do chia khoa di cho khac
		if((x==CK[i].x && y==CK[i].y) || (x==CK[i].x && y-1==CK[i].y)){
			++DemCK;
			CK[i].x=30;
			CK[i].y=30;
		}
	}
}
//Ham kiem tra cua
void KTCua(int &x, int &y){
	for(int i=0; i<6; i++){
		if((x==Cua[i].x && y==Cua[i].y) || (x==Cua[i].x && y-1==Cua[i].y)){
			//Neu du chia khoa
			CheckCua=true;//Xac nhan vao cua
			if(DemCK==3){
				// if(MChoi==3){
				// 	time(&)
				// }
				end();	//Chuyen sang phan ket thuc
			}
			//Neu chua du chia khoa
			else{
				if(hD==1){
					x--;
				}
				else if(hD==-1){
					x++;
				}
			}
		}
		//In lai cua
		for(int j=0; j<6; j++){
			GoTo(Cua[j].x,Cua[j].y);
			DoiMau(0,9);
			printf("%c",177);
			DoiMau(0,11);
		}
	}
	CheckCua=false;//xac nhan ra khoi cua
}
//Ham kiem tra thang leo
void KTThangLeo(int &x, int &y){
	for(int i=0; i<=TDvaD; i++){
		if((x==ThangLDi[i].x && y==ThangLDi[i].y) || (x==ThangLDi[i].x && y-1==ThangLDi[i].y)){
			char phim=getch();
			if(phim=='s'){
				int xC=x, yC=y;
				for(int j=0; j<=(ThangLDi[i].y-ThangLDen[i].y-1); j++){
					Sleep(50);
					XNV(xC,yC);
					Sleep(50);
					NV(ThangLDi[i].x,ThangLDi[i].y-j);
					xC=ThangLDi[i].x; yC=ThangLDi[i].y-j;
				}
				Sleep(50);
				XNV(xC,yC);
				Sleep(50);
				NV(ThangLDen[i].x,ThangLDen[i].y);
				x=ThangLDen[i].x; y=ThangLDen[i].y;
			}
			else break;
		}
	}
}
//Ham kiem tra khoi dat
void KTKhoiDat(int &x, int &y){
	if(hR==1){
		for(int i=0; i<=DemKD; i++){
			if(x==KhoiDat[i].x && y==KhoiDat[i].y){
				if(hD==1){
					KhoiDat[i].x++;
					for(int h=0; h<=DM; h++){
						if(Map[h].VT.x==KhoiDat[i].x && Map[h].VT.y==KhoiDat[i].y){
							x--;
							KhoiDat[i].x--;
						}
					}
					GoTo(KhoiDat[i].x,KhoiDat[i].y);
					DoiMau(0,9);
					printf("%c",254);
					DoiMau(0,11);
				}
				else if(hD==-1){
					KhoiDat[i].x--;
					for(int h=0; h<=DM; h++){
						if(Map[h].VT.x==KhoiDat[i].x && Map[h].VT.y==KhoiDat[i].y){
							x++;
							KhoiDat[i].x++;
						}
					}
					GoTo(KhoiDat[i].x,KhoiDat[i].y);
					DoiMau(0,9);
					printf("%c",254);
					DoiMau(0,11);
				}
			}
		}
	hR=0;
	}
}

//HAM QUANG TRONG//
//Ham dieu khien nhan vat
int DieuKhien(int &x, int &y){
	while(1){
		HienThi();
		KTThangLeo(x,y);
		char phim=getch();
		//Sang phai
		if(phim=='d'){
			Phai(x,y);
		}
		//Sang trai
		else if(phim=='a'){
			Trai(x,y);
		}
		//Nhay len
		else if(phim=='w'){
			Nhay(x,y);
			RoiTD(x,y);
			KTGai(x,y);
		}
		else if(phim=='k'){
			char hack[100], passhack[]={"hiephoimeoden"};
			GoTo(0,33);
			gets(hack);
			if(strcmp(strlwr(hack),passhack)==0){
				CheckCua=true;
				end();
			}
			DieuKhien(x,y);
		}
		else{
			continue;
		}
		end();
	}
}
//Ham đi sang phai
void Phai(int &x, int &y){
	int xC=x, yC=y; //Ghi lai toa do cu
	hD=1; x++;
	KTTN(x,y);
	XNV(xC,yC);
	NV(x,y);
	RoiTD(x,y);
	KTGai(x,y);
}
//Ham đi sang trai
void Trai(int &x, int &y){
	int xC=x, yC=y; //Ghi lai toa do cu
	hD=-1; x--;
	KTTN(x,y);
	XNV(xC,yC);
	NV(x,y);
	RoiTD(x,y);
	KTGai(x,y);
}
//Ham bat nhay;
void Nhay(int &x, int &y){
	int xC=x, yC=y, dc;	//dc: đo cao nv da nhay
	char phim=getch();
	if(phim=='d'){
		hD=1;
	//len lan 1
		x++; y--;
		KTTN(x,y);
		Sleep(20);
		XNV(xC,yC);
		Sleep(20);
		NV(x,y);
		xC=x; yC=y;
	//len lan 2
		x++; y--;
		KTTN(x,y);
		Sleep(20);
		XNV(xC,yC);
		Sleep(20);
		NV(x,y);
		xC=x; yC=y;
		dc=2;
	}
	else if(phim=='a'){
		hD=-1; 
	//len lan 1
		x--; y--;
		KTTN(x,y);
		Sleep(20);
		XNV(xC,yC);
		Sleep(20);
		NV(x,y);
		xC=x; yC=y;
	//len lan 2
		x--; y--;
		KTTN(x,y);
		Sleep(20);
		XNV(xC,yC);
		Sleep(20);
		NV(x,y);
		xC=x; yC=y;
		dc=2;
	}
	//Nhay xa
	else if(phim=='w'){
		phim=getch();
		if(phim=='d'){
			hD=1; 
		//len lan 1
			x++; y--;
			KTTN(x,y);
			Sleep(20);
			XNV(xC,yC);
			Sleep(20);
			NV(x,y);
			xC=x; yC=y;
		//len lan 2
			x++; y--;
			KTTN(x,y);
			Sleep(20);
			XNV(xC,yC);
			Sleep(20);
			NV(x,y);
			xC=x; yC=y;
		//len lan 3
			x++; y--;
			KTTN(x,y);
			Sleep(20);
			XNV(xC,yC);
			Sleep(20);
			NV(x,y);
			xC=x; yC=y;
		//đi ngang lan 1
			x++;
			KTTN(x,y);
			Sleep(20);
			XNV(xC,yC);
			Sleep(20);
			NV(x,y);
			xC=x; yC=y;
			dc=3;
		//đi ngang lan 2
			x++;
			KTTN(x,y);
			Sleep(20);
			XNV(xC,yC);
			Sleep(20);
			NV(x,y);
			xC=x; yC=y;
			dc=3;
		}
		else if(phim=='a'){
			hD=-1; 
		//len lan 1
			x--; y--;
			KTTN(x,y);
			Sleep(20);
			XNV(xC,yC);
			Sleep(20);
			NV(x,y);
			xC=x; yC=y;
		//len lan 2
			x--; y--;
			KTTN(x,y);
			Sleep(20);
			XNV(xC,yC);
			Sleep(20);
			NV(x,y);
			xC=x; yC=y;
		//len lan 3
			x--; y--;
			KTTN(x,y);
			Sleep(20);
			XNV(xC,yC);
			Sleep(20);
			NV(x,y);
			xC=x; yC=y;
		//đi ngang lan 1
			x--;
			KTTN(x,y);
			Sleep(20);
			XNV(xC,yC);
			Sleep(20);
			NV(x,y);
			xC=x; yC=y;
			dc=3;
		//đi ngang lan 2
			x--;
			KTTN(x,y);
			Sleep(20);
			XNV(xC,yC);
			Sleep(20);
			NV(x,y);
			xC=x; yC=y;
			dc=3;
		}
		//Chua phat trien them
		else DieuKhien(x,y);
	}
	else DieuKhien(x,y);
	//Roi xuong
	for(int i=dc; i>0; i--){
		if(hD==1){
			x++; y++;
			KTTN(x,y);
			Sleep(20);
			XNV(xC,yC);
			Sleep(20);
			NV(x,y);
			xC=x; yC=y;
		}
		else if(hD==-1){
			x--; y++;
			KTTN(x,y);
			Sleep(20);
			XNV(xC,yC);
			Sleep(20);
			NV(x,y);
			xC=x; yC=y;
		}
	}
}


//Ham thay đoi mau
void DoiMau(int MauNen, int MauChu){
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); //Đau ra
    int Mau = MauNen * 16 + MauChu; //Cong thuc tao mau
    SetConsoleTextAttribute(hStdout, Mau); //Ham thay đoi mau
}
//Ham di chuyển con tro
void GoTo(SHORT X, SHORT Y){
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); //Đau ra
    COORD ToaDo; //Tao toa đo
    ToaDo.X = X;
    ToaDo.Y = Y;
	SetConsoleCursorPosition(hStdout, ToaDo); //Ham di chuyen
}
//Ham an con tro
void ShowCur(bool CursorVisibility){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;
    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = CursorVisibility;
    SetConsoleCursorInfo(handle, &ConCurInf);
}
//Ham lay toa đo x cua con tro
int where_x(){
	CONSOLE_SCREEN_BUFFER_INFO coninfo; 
	GetConsoleScreenBufferInfo (GetStdHandle(STD_OUTPUT_HANDLE), &coninfo); //Truyen vao đau ra va toa đo 
	return coninfo.dwCursorPosition.X; //Toa đo x cua con tro
}
//Ham lay toa đo y cua con tro
int where_y(){
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	GetConsoleScreenBufferInfo (GetStdHandle(STD_OUTPUT_HANDLE), &coninfo); //Truyen vao đau ra va toa đo
	return coninfo.dwCursorPosition.Y; //Toa đo y cua con tro
}

//In nhan vat
void NV(int x, int y){
	DoiMau(0,9);
	//Chan
	GoTo(x, y);
	printf("%c",19);
	//Đau
	GoTo(x, y-1);
	printf("%c",64);
	DoiMau(0,11);
}
//Xoa nhan vat
void XNV(int x, int y){
	//Chan 
	GoTo(x, y);
	printf(" ");
	//Đau
	GoTo(x, y-1);
	printf(" ");
}
//Ghi toa đo map
void GhiTD(){
	Map[DM].VT.x=where_x()-1;
    Map[DM].VT.y=where_y();
    Map[DM].kt=1;
    DM++;
}


//MAP GAME	(178)
void Map_3(int canh){
	nv.x=4; nv.y=27;
	system("cls");
	DoiMau(0,11);
	Khung(201,187,200,188,205,186);
	TCua(5,10);
	TGai(20,5,29,19,4);
	TGai(65,5,23,64,3);
	TGai(37,27,30,36,23);
	TGai(107,27,7,105,21);
	TChiaKhoa(11,4,1);
	TChiaKhoa(72,26,2);
	TChiaKhoa(101,16,3);
	TThangLeo(1,7,8,-1);
	TThangLeo(92,5,4,1);
	TKhoiDat(13,27);
	TKhoiDat(11,22);
	TKhoiDat(79,18);
	TKhoiDat(93,27);
	TCongTac(84,26,2,27);
	TCongTac(27,8,95,8);
	//Thang 1
	GoTo(1,6);
	printf("%c",canh);
    GhiTD();
	GoTo(1,15);
	printf("%c",canh);
    GhiTD();
	//Thang 2
	GoTo(92,4);
	printf("%c",canh);
    GhiTD();
	GoTo(92,9);
	printf("%c",canh);
    GhiTD();
	//Tang 3
	for(int i=6; i<=11; i++){
		GoTo(4,i);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=4; j<=9; j++){
		GoTo(j,11);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=4; j<=43; j++){
		GoTo(j,6);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=12; j<=15; j++){
		GoTo(j,11);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=15; j<=43; j++){
		GoTo(j,10);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=19,i=5; j<=42; j+=6){
		GoTo(j,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+1,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+2,i);
		printf("%c",canh);
		GhiTD();
	}
	for(int j=43; j<=65; j++){
		GoTo(j,5);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=65; j<=89; j++){
		GoTo(j,6);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=69,i=5; j<=88; j+=5){
		GoTo(j,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+1,i);
		printf("%c",canh);
		GhiTD();
	}
	GoTo(89,5);
	printf("%c",canh);
    GhiTD();
	for(int j=46; j<=48; j++){
		GoTo(j,10);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=52; j<=54; j++){
		GoTo(j,9);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=58; j<=96; j++){
		GoTo(j,9);
		printf("%c",canh);
        GhiTD();
	}
	GoTo(94,8);
	printf("%c",canh);
    GhiTD();
	GoTo(94,7);
	printf("%c",canh);
    GhiTD();
	for(int i=4; i<=8; i++){
		GoTo(93,i);
		printf("%c",canh);
        GhiTD();
	}
	for(int i=6; i<=9; i++){
		GoTo(97,i);
		printf("%c",canh);
        GhiTD();
	}
	//Tang 2
	for(int i=16; i<=23; i++){
		for(int j=1; j<=3; j++){
			GoTo(j,i);
			printf("%c",canh);
			GhiTD();
		}
	}
	for(int i=19; i<=23; i++){
		for(int j=4; j<=5; j++){
			GoTo(j,i);
			printf("%c",canh);
			GhiTD();
		}
	}
	for(int j=6; j<=14; j++){
		GoTo(j,23);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=14; j<=18; j++){
		GoTo(j,22);
		printf("%c",canh);
        GhiTD();
	}
	for(int i=17; i<=21; i++){
		GoTo(18,i);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=20,i=16; j<=28; j+=3){
		GoTo(j,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+1,i);
		printf("%c",canh);
		GhiTD();
		i--;
	}
	for(int j=29,i=15; j<=34; j+=3){
		GoTo(j,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+1,i);
		printf("%c",canh);
		GhiTD();
		i++;
	}
	for(int j=35; j<=37; j++){
		GoTo(j,17);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=41; j<=43; j++){
		GoTo(j,17);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=46; j<=47; j++){
		GoTo(j,16);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=54; j<=55; j++){
		GoTo(j,16);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=50; j<=51; j++){
		GoTo(j,14);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=58; j<=60; j++){
		GoTo(j,17);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=64; j<=66; j++){
		GoTo(j,17);
		printf("%c",canh);
        GhiTD();
	}
	for(int i=12; i<=19; i++){
		for(int j=67; j<=68; j++){
			GoTo(j,i);
			printf("%c",canh);
			GhiTD();
		}
	}
	for(int i=13; i<=19; i++){
		for(int j=69; j<=70; j++){
			GoTo(j,i);
			printf("%c",canh);
			GhiTD();
		}
	}
	for(int i=15; i<=19; i++){
		for(int j=71; j<=72; j++){
			GoTo(j,i);
			printf("%c",canh);
			GhiTD();
		}
	}
	for(int j=73; j<=83; j++){
		GoTo(j,19);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=84,i=18; j<=95; j+=3){
		GoTo(j,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+1,i);
		printf("%c",canh);
		GhiTD();
		i--;
	}
	for(int i=13; i<=18; i++){
		for(int j=97; j<=99; j++){
			GoTo(j,i);
			printf("%c",canh);
			GhiTD();
		}
	}
	for(int j=100; j<=110; j++){
		GoTo(j,13);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=100; j<=102; j++){
		GoTo(j,18);
		printf("%c",canh);
        GhiTD();
	}
	GoTo(103,19);
	printf("%c",canh);
    GhiTD();
	//Tang 1
	for(int i=24; i<=27; i++){
		for(int j=23; j<=36; j++){
			GoTo(j,i);
			printf("%c",canh);
			GhiTD();
		}
	}
	for(int j=37,i=24; j<=48; j+=4){
		GoTo(j,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+1,i);
		printf("%c",canh);
		GhiTD();
		i-=2;
	}
	for(int j=49,i=22; j<=63; j+=5){
		GoTo(j,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+1,i);
		printf("%c",canh);
		GhiTD();
		i+=2;
	}
	for(int i=24; i<=27; i++){
		for(int j=66; j<=68; j++){
			GoTo(j,i);
			printf("%c",canh);
			GhiTD();
		}
	}
	for(int i=23; i<=27; i++){
		for(int j=69; j<=70; j++){
			GoTo(j,i);
			printf("%c",canh);
			GhiTD();
		}
	}
	GoTo(69,22);
	printf("%c",canh);
    GhiTD();
	GoTo(71,24);
	printf("%c",canh);
    GhiTD();
	for(int j=71; j<=84; j++){
		GoTo(j,25);
		printf("%c",canh);
        GhiTD();
	}
	for(int i=24; i<=27; i++){
		for(int j=102; j<=103; j++){
			GoTo(j,i);
			printf("%c",canh);
			GhiTD();
		}
	}
	for(int i=22; i<=27; i++){
		for(int j=104; j<=105; j++){
			GoTo(j,i);
			printf("%c",canh);
			GhiTD();
		}
	}
	for(int i=19; i<=27; i++){
		GoTo(106,i);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=107; j<=108; j++){
		GoTo(j,19);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=109; j<=110; j++){
		GoTo(j,17);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=112; j<=113; j++){
		GoTo(j,15);
		printf("%c",canh);
        GhiTD();
	}
}
void Map_2(int canh){
	nv.x=4; nv.y=27;
	system("cls");
	DoiMau(0,11);
	Khung(201,187,200,188,205,186);
	TCua(2,4);
	TGai(10,22,3,8,20);
	TGai(17,24,3,15,22);
	TGai(37,27,74,35,26);
	TChiaKhoa(1,19,1);
	TChiaKhoa(113,22,2);
	TChiaKhoa(23,5,3);
	TThangLeo(6,6,7,-1);
	TThangLeo(21,11,6,-1);
	TThangLeo(105,7,7,-1);
	TThangLeo(7,22,5,1);
	TKhoiDat(34,16);
	TCongTac(9,10,67,5);
	//Thang 1
	GoTo(21,10);
	printf("%c",canh);
    GhiTD();
	//Thang 2
	GoTo(105,6);
	printf("%c",canh);
    GhiTD();
	//Thang 3
	GoTo(7,21);
	printf("%c",canh);
    GhiTD();
	GoTo(7,27);
	printf("%c",canh);
    GhiTD();
	//Tang 2
	for(int j=1; j<=6; j++){
		GoTo(j,5);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=5; j<=9; j++){
		GoTo(j,13);
		printf("%c",canh);
        GhiTD();
	}
	for(int i=5; i<=13; i++){
		GoTo(5,i);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=13; j<=16; j++){
		GoTo(j,13);
		printf("%c",canh);
        GhiTD();
	}
	for(int i=10; i<=16; i++){
		GoTo(20,i);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=20; j<=37; j++){
		GoTo(j,17);
		printf("%c",canh);
        GhiTD();
	}
	for(int i=13; i<=16; i++){
		for(int j=28; j<=29; j++){
			GoTo(j,i);
			printf("%c",canh);
			GhiTD();
		}
	}
	for(int j=37,i=16; j<=45; j+=3){
		GoTo(j,i);
		printf("%c",canh);
		GhiTD();
		i-=2;
	}
	for(int j=48; j<=50; j++){
		GoTo(j,11);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=57; j<=59; j++){
		GoTo(j,11);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=65; j<=67; j++){
		GoTo(j,6);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=72,i=6; j<=86; j+=7){
		GoTo(j,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+1,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+2,i);
		printf("%c",canh);
		GhiTD();
	}
	for(int j=87; j<=93; j++){
		GoTo(j,6);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=97; j<=99; j++){
		GoTo(j,6);
		printf("%c",canh);
        GhiTD();
	}
	//Tang 1
	for(int i=21; i<=27; i++){
		for(int j=1; j<=2; j++){
			GoTo(j,i);
			printf("%c",canh);
			GhiTD();
		}
	}
	for(int i=21; i<=27; i++){
		for(int j=8; j<=9; j++){
			GoTo(j,i);
			printf("%c",canh);
			GhiTD();
		}
	}
	for(int i=23; i<=27; i++){
		for(int j=10; j<=16; j++){
			GoTo(j,i);
			printf("%c",canh);
			GhiTD();
		}
	}
	for(int i=25; i<=27; i++){
		for(int j=17; j<=26; j++){
			GoTo(j,i);
			printf("%c",canh);
			GhiTD();
		}
	}
	for(int j=27; j<=36; j++){
		GoTo(j,27);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=39; j<=40; j++){
		GoTo(j,25);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=45; j<=47; j++){
		GoTo(j,24);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=49; j<=50; j++){
		GoTo(j,22);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=52; j<=54; j++){
		GoTo(j,20);
		printf("%c",canh);
        GhiTD();
	}
	for(int i=17; i<=19; i++){
		GoTo(49,i);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=62; j<=68; j++){
		GoTo(j,14);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=59; j<=70; j++){
		GoTo(j,19);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=71; j<=74; j++){
		GoTo(j,17);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=79; j<=82; j++){
		GoTo(j,17);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=86; j<=89; j++){
		GoTo(j,15);
		printf("%c",canh);
        GhiTD();
	}
	GoTo(94,15);
	printf("%c",canh);
    GhiTD();
	for(int j=97; j<=100; j++){
		GoTo(j,12);
		printf("%c",canh);
        GhiTD();
	}
	for(int i=6; i<=13; i++){
		GoTo(104,i);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=104; j<=106; j++){
		GoTo(j,14);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=107; j<=110; j++){
		GoTo(j,16);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=103; j<=108; j++){
		GoTo(j,22);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=111; j<=113; j++){
		GoTo(j,19);
		printf("%c",canh);
        GhiTD();
	}
	for(int i=24; i<=27; i++){
		for(int j=111; j<=113; j++){
			GoTo(j,i);
			printf("%c",canh);
			GhiTD();
		}
	}
}
void Map_1(int canh){
	nv.x=2; nv.y=27;
	system("cls");
	DoiMau(0,11);
	Khung(201,187,200,188,205,186);
	TCua(111,22);
	TGai(11,27,11,9,24);
	TGai(23,27,20,18,5);
	TGai(54,27,23,78,24);
	TGai(80,27,15,78,24);
	TGai(106,27,8,104,25);
	TChiaKhoa(27,20,1);
	TChiaKhoa(50,22,2);
	TChiaKhoa(96,5,3);
	TThangLeo(51,11,5,1);
	TKhoiDat(48,27);
	TCongTac(43,8,12,7);
	TCongTac(108,21,69,11);
	//Thang 1
	GoTo(51,10);
	printf("%c",canh);
    GhiTD();
	GoTo(51,16);
	printf("%c",canh);
    GhiTD();
	//Khu 1
	for(int i=25; i<=27; i++){
		for(int j=5; j<=10; j++){
			GoTo(j,i);
			printf("%c",canh);
			GhiTD();
		}
	}
	for(int j=14; j<=16; j++){
		GoTo(j,25);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=19; j<=21; j++){
		GoTo(j,23);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=4,i=16; j<=18; j+=5){
		GoTo(j,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+1,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+2,i);
		printf("%c",canh);
		GhiTD();
		i+=2;
	}
	for(int j=1; j<=2; j++){
		GoTo(j,13);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=6; j<=8; j++){
		GoTo(j,11);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=10; j<=12; j++){
		GoTo(j,8);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=17; j<=19; j++){
		GoTo(j,6);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=11; j<=13; j++){
		GoTo(j,5);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=3; j<=5; j++){
		GoTo(j,6);
		printf("%c",canh);
        GhiTD();
	}
	for(int i=6; i<=27; i++){
		GoTo(22,i);
		printf("%c",canh);
        GhiTD();
	}
	//Khu 2
	for(int i=22; i<=27; i++){
		GoTo(27,i);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=31,i=22; j<=42; j+=6){
		GoTo(j,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+1,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+2,i);
		printf("%c",canh);
		GhiTD();
	}
	for(int i=21; i<=27; i++){
		GoTo(43,i);
		printf("%c",canh);
        GhiTD();
	}
	for(int i=19; i<=20; i++){
		for(int j=43; j<=52; j++){
			GoTo(j,i);
			printf("%c",canh);
			GhiTD();
		}
	}
	for(int i=17; i<=18; i++){
		for(int j=48; j<=52; j++){
			GoTo(j,i);
			printf("%c",canh);
			GhiTD();
		}
	}
	for(int i=5; i<=15; i++){
		GoTo(52,i);
		printf("%c",canh);
        GhiTD();
	}
	GoTo(51,5);
	printf("%c",canh);
    GhiTD();
	GoTo(43,10);
	printf("%c",canh);
    GhiTD();
	for(int j=45; j<=46; j++){
		GoTo(j,13);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=40; j<=43; j++){
		GoTo(j,13);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=35; j<=37; j++){
		GoTo(j,10);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=39; j<=42; j++){
		GoTo(j,7);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=45; j<=48; j++){
		GoTo(j,4);
		printf("%c",canh);
        GhiTD();
	}
	//Khu 3
	GoTo(52,27);
	printf("%c",canh);
    GhiTD();
	for(int j=56,i=25; j<=79; j+=8){
		GoTo(j,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+1,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+2,i);
		printf("%c",canh);
		GhiTD();
	}
	for(int i=25; i<=27; i++){
		for(int j=77; j<=79; j++){
			GoTo(j,i);
			printf("%c",canh);
			GhiTD();
		}
	}
	for(int j=83,i=25; j<=94; j+=6){
		GoTo(j,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+1,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+2,i);
		printf("%c",canh);
		GhiTD();
	}
	for(int i=25; i<=27; i++){
		for(int j=95; j<=97; j++){
			GoTo(j,i);
			printf("%c",canh);
			GhiTD();
		}
	}
	for(int i=22; i<=27; i++){
		for(int j=98; j<=101; j++){
			GoTo(j,i);
			printf("%c",canh);
			GhiTD();
		}
	}
	for(int i=26; i<=27; i++){
		for(int j=102; j<=105; j++){
			GoTo(j,i);
			printf("%c",canh);
			GhiTD();
		}
	}
	for(int j=108; j<=113; j++){
		GoTo(j,23);
		printf("%c",canh);
        GhiTD();
	}
	for(int j=81,i=13; j<=95; j+=5){
		GoTo(j,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+1,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+2,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+3,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+4,i);
		printf("%c",canh);
		GhiTD();
		i+=2;
	}
	for(int j=80,i=9; j<=98; j+=5){
		GoTo(j,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+1,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+2,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+3,i);
		printf("%c",canh);
		GhiTD();
		GoTo(j+4,i);
		printf("%c",canh);
		GhiTD();
		i--;
	}
	GoTo(69,12);
	printf("%c",canh);
    GhiTD();
	for(int j=72; j<=75; j++){
		GoTo(j,12);
		printf("%c",canh);
        GhiTD();
	}
}

//Ham tao cua
void TCua(int x, int y){
	//Ghi toa do cua
	Cua[0].x=x; Cua[0].y=y;
	Cua[1].x=x; Cua[1].y=y-1;
	Cua[2].x=x+1; Cua[2].y=y;
	Cua[3].x=x+1; Cua[3].y=y-1;
	Cua[4].x=x+2; Cua[4].y=y;
	Cua[5].x=x+2; Cua[5].y=y-1;
	//In cua ra
	for(int i=0; i<6; i++){
		GoTo(Cua[i].x,Cua[i].y);
		DoiMau(0,9);
		printf("%c",176);
		DoiMau(0,11);
	}
}
//Ham tao chia khoa
void TChiaKhoa(int x, int y, int k){
	CK[k-1].x=x; CK[k-1].y=y; //Thiet lap toa do cho chia khoa
	GoTo(x,y);
	DoiMau(0,9);
	printf("*");
	DoiMau(0,11);
}
//Ham tao cong tac
void  TCongTac(int xD, int yD, int xCT, int yCT){
	for(int i=0; i<2; i++){
		CuaChan[DemCC].VT.x=xD; CuaChan[DemCC].VT.y=yD+i; CuaChan[DemCC].kt=DemCT;
		GoTo(xD,yD+i);
		DoiMau(0,9);
		printf("%c",240);
		DoiMau(0,11);
		GhiTD();
		DemCC++;
	}
	CTac[DemCT].x=xCT; CTac[DemCT].y=yCT;
	GoTo(xCT,yCT);
	DoiMau(0,9);
	printf("%c",29);
	DoiMau(0,11);
	DemCT++;
}
//Ham tao khoi dat
void TKhoiDat(int x, int y){
	KhoiDat[DemKD].x=x; KhoiDat[DemKD].y=y;
	GoTo(x,y);
	DoiMau(0,9);
	printf("%c",254);
	DoiMau(0,11);
	DemKD++;
}
//Ham tao gai
void TGai(int xD, int yD, int sl, int xQL, int yQL){
	//Tao va ghi toa do gai
	for(int i=0; i<sl; i++){
		Gai[DemGai].VT.x=xD+i; Gai[DemGai].VT.y=yD; Gai[DemGai].kt=GQL;
		GoTo(xD+i,yD);
		DoiMau(0,9);
		printf("%c",30);
		DoiMau(0,11);
		DemGai++;
	}
	GaiQL[GQL].x=xQL; GaiQL[GQL].y=yQL;	//Thiet lap vi tri quay lai khi trung gai
	GQL++;	//Thay doi qua vi tri quay lai khac
}
//Ham tao thang leo
void TThangLeo(int xD, int yD, int KThuoc, int h){
	for(int i=0; i<KThuoc; i++){
		ThangL[DemTL].VT.x=xD; ThangL[DemTL].VT.y=yD+i; ThangL[DemTL].kt=TDvaD;
		GoTo(xD,yD+i);
		DoiMau(0,9);
		printf("%c",216);
		DoiMau(0,11);
		GhiTD();	//Ghi toa do de thang nhu 1 vat the khong cho vat di tiep
		DemTL++;
	}
	//Thiet lap toa do diem den va di cho thang
	if(h==1){
		ThangLDi[TDvaD].x=xD-1; ThangLDi[TDvaD].y=yD+KThuoc-1;
	}
	else if(h==-1){
		ThangLDi[TDvaD].x=xD+1; ThangLDi[TDvaD].y=yD+KThuoc-1;
	}
	ThangLDen[TDvaD].x=xD; ThangLDen[TDvaD].y=yD-2;
	TDvaD++;	//Thay doi qua vi tri den va di cua thang khac 
}
//Ham tao khung
void Khung(int gtt, int gtp, int gdt, int gdp, int cn, int cd){
	for(int i=0; i<=28; i++){
		for(int j=0; j<=114; j++){
			if(i==0 || i==28 || j==0 || j==114){
				if(i==0 && j==0){
					printf("%c",gtt);
                    GhiTD();
                }
				else if(i==0 && j==114){
					printf("%c",gtp);
                    GhiTD();
                }
				else if(i==28 && j==0){
					printf("%c",gdt);
                    GhiTD();
                }
				else if(i==28 && j==114){
					printf("%c",gdp);
                    GhiTD();
                }
				else{
					if(j==0 || j==114){
					    printf("%c",cd);
                        GhiTD();
					}
					else
						printf("%c",cn);
                        GhiTD();
				}
			}
			else
				printf(" ");
		}
		printf("\n");
	}
}


//Ham hien thi dang ky, dang nhap
int DKy_DNhap(){
    system("cls");
    //Khoi tao bien chon phuong an va bien chon phuong an truoc đo
    int  chon = 1, choncu = 0;
    //Noi dung
    DoiMau(0,9);
    GoTo(45,12);
    printf("%c %c %c %c THE RIVER %c %c %c %c",3,4,5,6,6,5,4,3);
	DoiMau(0,11);
    GoTo(54,14);
    printf("DANG KY");
    GoTo(53,15);
    printf("DANG NHAP");
    GoTo(1,27);
    printf("ESC: thoat game!");
	//Di chuyen con tro
    while(1){
    	DC_Chon_DKy_DNhap(chon,choncu); //Hien vi tri con tro đe chon
		char lenh;
		if(kbhit()){ //Kiem tra bo đem ban phim
			lenh=getch();
			if(lenh==13)
		 		break; //Dung vong lap (chon phuong an)
 			if(lenh==80){
				if(chon<2){
					chon++;
					choncu=chon-1;
					DC_Chon_DKy_DNhap(chon,choncu);
				}
			}
			if(lenh==72){
				if(chon>1){
					chon--; 
					choncu=chon+1;	
					DC_Chon_DKy_DNhap(chon,choncu);
				}
			}
			if(lenh==27)	//Thoat game
				return 0;
		}
	}
    //Dang ky
    if(chon==1){
		TaoTK();
	}
	//Dang nhap
	if(chon==2){
		DangNhapTK();
	}
}
//Ham hien thi con tro tai phuong an chon
void DC_Chon_DKy_DNhap(int chon, int choncu){
    //1=> 2->1
    if(chon==1){
		if(choncu==2){
			GoTo(51,15);
			DoiMau(0,11);
    		printf("  DANG NHAP");
		}
		GoTo(52,14);
		DoiMau(0,9);
		printf("%c DANG KY",16);
		DoiMau(0,11);
	}
    //2=> 1->2 hoặc 3->2
	if(chon==2){
		if(choncu==1){
			GoTo(52,14);
			DoiMau(0,11);
    		printf("  DANG KY");
		}
		GoTo(51,15);
		DoiMau(0,9);
		printf("%c DANG NHAP",16);
		DoiMau(0,11);
	}
}
//Ham tao tai khoan
void TaoTK(){
	system("cls");
	GoTo(44,10);
	DoiMau(0,9);
    printf("-----DANG KI TAI KHOAN-----\n");
	DoiMau(0,11);
    printf("Tai Khoan: ");
    gets(TK.name);
	Sleep(1000);

    nhapMatKhau:
	system("cls");
	GoTo(44,10);
	DoiMau(0,9);
    printf("-----DANG KI TAI KHOAN-----\n");
	DoiMau(0,11);
    printf("Mat Khau: ");
    gets(TK.pass); 
    if(CheckPass(TK.pass)){
		GoTo(45,14);
        printf("Nhap mat khau thanh cong!");
		Sleep(1000);
		goto nhapNgaySinh;
    }
    else{
		GoTo(30,14);
        printf("Mat khau phai co ki tu dat biet, chu thuong, chu hoa!!!");
		GoTo(43,15);
        printf("Vui long nhap lai mat khau !");
		Sleep(1000);
        goto nhapMatKhau;
    }

    nhapNgaySinh:
	system("cls");
	GoTo(44,10);
	DoiMau(0,9);
    printf("-----DANG KI TAI KHOAN-----\n");
	DoiMau(0,11);
    printf("Ngay sinh(xx/yy/zzzz): ");
    scanf("%d/%d/%d",&TK.NgaySinh.ngay,&TK.NgaySinh.thang,&TK.NgaySinh.nam);
    getchar();
    if(CheckDate()){
        TinhTuoi();
        if(TK.tuoi<13){
			GoTo(45,14);
        	printf("Do tuoi khong duoc phep choi game nay!!!");
			Sleep(1000);
			DKy_DNhap();
        }
        char tenFile[50];
        strcpy(tenFile,TK.name);
        strcat(tenFile,".txt"); //Tao file theo ten tai khoan
        FILE* file;
        file=fopen(tenFile,"w");
        if(file==NULL){
			GoTo(29,14);
            printf("Co loi Khong the tao hoac mo duoc file luu tai khoan mat khau!!!");
			Sleep(1000);
            DKy_DNhap();
        }
        fprintf(file,"%s",TK.pass);
        fclose(file);
		GhiLuotChoi();
    }
    else{
		GoTo(45,14);
        printf("Ngay sinh khong hop le !!!");
		Sleep(1000);
        goto nhapNgaySinh;
    }
}
// Ham dang nhap tai khoan
void DangNhapTK(){
    Nhap:
	system("cls");
	GoTo(42,10);
	DoiMau(0,9);
    printf("-----DANG NHAP TAI KHOAN-----\n");
	DoiMau(0,11);
    printf("Tai Khoan: ");
    gets(TK.name);
    FILE* file;
    char tenFile[50];
    strcpy(tenFile,TK.name);
    strcat(tenFile,".txt");
    file=fopen(tenFile,"r");
    if(file==NULL){
		GoTo(44,14);
        printf("Tai Khoan Khong Ton Tai !!!");
		Sleep(1000);
        DKy_DNhap();
    }
    char MatKhau[50];
    fscanf(file,"%s",&MatKhau);
    printf("\nMat Khau: ");
    gets(TK.pass);
    if(strcmp(TK.pass,MatKhau)==0){
		GoTo(46,14);
        printf("DANG NHAP THANH CONG!!");
		Sleep(1000);
		GhiLuotChoi();
    }
    else{
		GoTo(47,14);
        printf("Mat khau khong dung!!!");
		Sleep(1000);
        goto Nhap;
    }
}
// Ham kiem tra chuoi co ki tu dat biet, chu thuong, chu hoa
bool CheckPass(char a[]){
    size_t len=strlen(a);
    for(int i=0; i<len; i++){
        //Kiem tra ki tu dac biet
        if((a[i]>=33 && a[i]<=47) || (a[i]>=58 && a[i]<=64) || (a[i]>=91 && a[i]<=96)){
            for(int j=0; j<len; j++){
                //Kiem tra chu thuong
                if(a[j]>=97 && a[j]<=122){
                    for(int z=0; z<len; z++){
                        //Kiem tra chu hoa
                        if((a[z]>=65 && a[z]<=90)){
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}
//Ham kiem tra ngay thang nam
int CheckDate(){
    if(TK.NgaySinh.ngay>31|| TK.NgaySinh.ngay<=0 || TK.NgaySinh.nam<=0||TK.NgaySinh.thang>12|| TK.NgaySinh.thang<=0){
        return 0;
    }
    if(TK.NgaySinh.thang==1 || TK.NgaySinh.thang ==3|| TK.NgaySinh.thang==5|| TK.NgaySinh.thang==7|| TK.NgaySinh.thang==8|| TK.NgaySinh.thang==10|| TK.NgaySinh.thang==12){
        if(TK.NgaySinh.ngay<=31){
            return 1;
        }
		else return 0;
    }
	else if(TK.NgaySinh.thang==2){
        if((TK.NgaySinh.nam%400==0 || (TK.NgaySinh.nam%4==0 && TK.NgaySinh.nam%50==0))&& TK.NgaySinh.ngay<=28){
            return 1;
        }
		else{
            return 0;
        }
    }
    else {
        if(TK.NgaySinh.ngay<=30){
            return 1;
        }
    }
}
//Ham tinh tuoi 
void TinhTuoi(){
    time_t TTIME=time(0);
    tm* NOW=localtime(&TTIME);
    TK.tuoi=NOW->tm_year+1900-TK.NgaySinh.nam;
}
//Ham ghi luot choi
void GhiLuotChoi(){
	system("cls");
	GoTo(46,10);
	DoiMau(0,9);
    printf("-----TAO LUOT CHOI-----\n");
	DoiMau(0,11);
    FILE* file;
    char tenFile[50];
    strcpy(tenFile,TK.name);
    strcat(tenFile,".txt");
    file=fopen(tenFile,"a"); //strcat de noi ten thanh .txt
    if(file==NULL){
		GoTo(41,14);
        printf("File khong mo duoc hoac bi loi !!!");
        Sleep(1000);
		DKy_DNhap();
    }
    printf("Ten nhan vat: ");
    gets(GhiNV.username);
    fprintf(file,"\n%s",GhiNV.username);
    fclose(file);
	Menu();
}
//Ham ghi thoi gian ki luc
void GhiThoiGian(double KL){
	FILE* file;
    char tenFile[50];
    strcpy(tenFile,TK.name);
    strcat(tenFile,".txt");
    file=fopen(tenFile,"a");
	fprintf(file,"\n%f",KL);
	fclose(file);
}
// Ham xem ky luc
void xuatFileKiLuc(){
	system("cls");
    FILE* file;
    char pass[50];
    char tenFile[50];
    strcpy(tenFile,TK.name);
    strcat(tenFile,".txt");
    file=fopen(tenFile,"r");
    if(file==NULL){
        printf("\nFile khong mo duoc hoac bi loi !!!");
        exit(1);
    }
    fscanf(file,"%s",pass);
    int n=-1;
    do{
        n++;
        fscanf(file,"%30s",XuatNV[n].username);
        fscanf(file,"%30s", XuatNV[n].rank);
    }while(atof(XuatNV[n].rank)!=0);
    n--;
	system("cls");
	GoTo(54,5);
	DoiMau(0,9);
    printf("KI LUC\n");
	DoiMau(0,11);
    for(int i=0; i<=n-1; i++){
        int max=i;
        for (int j=i+1; j<=n; j++){
            if(atof(XuatNV[j].rank)<atof(XuatNV[max].rank))
                max=j;
        }
        DoiCho(XuatNV[i], XuatNV[max]);
    }
    for(int i=0; i<=n; i++){
        printf("%d\t\t%30s\t\t%.3f\n",i, XuatNV[i].username, atof(XuatNV[i].rank));
    }
	GoTo(1,27);
	printf("ENTER: quay lai MENU");
	char enter;
	while(1){
		enter=getch();
		if(enter==13)
    		fclose(file);
			Menu();
	}
}
//Ham doi cho
void DoiCho(NhanVat &a, NhanVat &b){
    // printf("\nhelo\n");
    NhanVat temp;
    strcpy(temp.rank,a.rank);
    strcpy(temp.username,a.username);
    strcpy(a.rank,b.rank);
    strcpy(a.username,b.username);
    strcpy(b.rank,temp.rank);
    strcpy(b.username,temp.username);
}


//Ham menu (chưa sửa nội dung)
void Menu(){
    system("cls");
    //Khoi tao bien chon phuong an va bien chon phuong an truoc đo
    int  chon = 1, choncu = 0;
    //Noi dung
    DoiMau(0,9);
    GoTo(45,12);
    printf("%c %c %c %c THE RIVER %c %c %c %c",3,4,5,6,6,5,4,3);
    GoTo(54,13);
	DoiMau(0,11);
    printf("BAT DAU");
    GoTo(53,14);
    printf("LUAT CHOI");
    GoTo(54,15);
    printf(" KY LUC");
    GoTo(51,16);
    printf("THONG TIN GAME ");
    GoTo(1,27);
    printf("ESC: thoat game!");
	//Di chuyen con tro
    while(1){
    	DC_Chon_Menu(chon,choncu); //Hien vi tri con tro đe chon
		char lenh;
		if(kbhit()){ //Kiem tra bo đem ban phim
			lenh=getch();
			if(lenh==13)
		 		break; //Dung vong lap (chon phuong an)
 			if(lenh==80){
				if(chon<4){
					chon++;
					choncu=chon-1;
					DC_Chon_Menu(chon,choncu);
				}
			}
			if(lenh==72){
				if(chon>1){
					chon--; 
					choncu=chon+1;	
					DC_Chon_Menu(chon,choncu);
				}
			}
			if(lenh==27)	//Thoat game
				return;
		}
	}
    //Bat dau game
    if(chon==1){
		time(&GhiNV.t1);
		Man_1();
	}
	//Luat choi
	if(chon==2){
		system("cls");
		DoiMau(0,9);
    	printf("\t\t\t\t\t------*LUAT CHOI------\n");
	    printf("\n");
		DoiMau(0,11);
		printf("\t\t Di chuyen bang cac phim:\n\t\t a: sang trai\t\td: sang phai\t\ts: leo len thang\n\t\t w + a: nhay gan sang trai\n\t\t w + w + a: nhay xa sang trai\n\t\t w + d: nhay gan sang phai\n\t\t w + w + d:nhay xa sang phai\n");
		printf("\n"); 
		printf("\t\t Nhiem vu cua ban la vuot qua cac cam bay va co quan de thu thap\n");
		printf("\t\t nhung chiec chia khoa that lac, va mo canh cua de qua mang ke tiep.\n");
		printf("\t\t Ban co 3 mang. Moi lan cham vao cam bay (gai nhon), ban se mat 1 mang\n");
		printf("\t\t HAY CAN THAN NHA!!!\n");
		printf("\n");
		printf("\t\t Thanh tich cua ban se duoc tinh bang thoi gian hoan thanh mang choi. Toc do\n");
		printf("\t\t cang nhanh thu hang cang cao.\n\t\t Hay hoan thanh nhat co the va HAY CAN THAN CAM BAY!\n");
		GoTo(1,27);
		printf("\nENTER: quay lai MENU\n");
		char enter;
		while(1){
			enter=getch();
			if(enter==13)
				Menu();
		}
	}
	//Phan ky luc
    if(chon==3){
    	xuatFileKiLuc();
    }
	//Phan thong tin ve game
    if(chon==4){
		system("cls");
		DoiMau(0,9);
		printf("\t\t\t\t\t\t------*THONG TIN GAME*------\n");
		printf("\n"); 
		DoiMau(0,11);
		printf("\t\t Ten game : The river\n");
		printf("\n");
		printf("\t\t Cot truyen game: Hai dua choi voi nhau tu nho den mot ngay mot dua bi hon me.Dua \n");
		printf("\t\t mong manh kia mo thay ban no bi ket trong mot khoang khong gian toi tam.Kieu nhu ranh gioi\n"); 
		printf("\t\t giua thien dang voi dia nguc va hanh trinh den noi do de dua ban ve bat dau\n");
		printf("\n");
		printf("\t\t Diem noi bat cua game: Game tao cho nguoi choi mot cam giac chua tung co game nao lam duoc\n");
		printf("\t\t Khi nguoi choi di qua cac man ma khong doc ki huong dan truoc khi choi se gap rat nhieu kho\n");
		printf("\t\t khan.Chung toi da co tinh tao ra ca buoc nhay mot cach co dinh khien cho nguoi choi di lai\n");
		printf("\t\t nhieu lan nham tim ra quy luat cua tro choi de co the qua man mot cach de dang ben canh do\n");
		printf("\t\t cac man cung se thay doi da dang khi nguoi choi co the qua man khien cho nguoi choi khong tro\n ");
		printf("\t\t nen nham chan.") ;
		// printf("\n");
		GoTo(1,27);
		printf("\nENTER: tiep theo\n");
		char enterQT;
		while(1){
			enterQT=getch();
			if(enterQT==13){
				system("cls");
				DoiMau(0,9);
				printf("\t\t\t\t\t\t------*THONG TIN NHOM*------\n");
				DoiMau(0,11);
				printf("\t\t Nhom truong: Le Dinh Khoi\n");
				printf("\t\t Mssv:\n");
				printf("\t\t Mail:\n");
				printf("\t\t Thanh vien : Do Van thanh Duoc\n");
				printf("\t\t Mssv:\n");
				printf("\t\t Mail:\n");
				printf("\t\t Thanh vien : Tran Phuong Anh\n");
				printf("\t\t Mssv:\n");
				printf("\t\t Mail:\n");
				printf("\t\t Thanh vien : Ngyen Van Dung\n");
				printf("\t\t Mssv:\n");
				printf("\t\t Mail:\n");
				GoTo(1,27);
				printf("\nENTER: quay lai MENU\n");
				char enterQV;
				while(1){
					enterQV=getch();
					if(enterQV==13)
						Menu();
				}
			}
		}
	}
}
//Ham hien thi con tro tai phuong an chon
void DC_Chon_Menu(int chon, int choncu){
    //1=> 2->1
    if(chon==1){
		if(choncu==2){
			GoTo(51,14);
			DoiMau(0,11);
    		printf("  LUAT CHOI");
		}
		GoTo(52,13);
		DoiMau(0,9);
		printf("%c BAT DAU",16);
		DoiMau(0,11);
	}
    //2=> 1->2 hoặc 3->2
	if(chon==2){
		if(choncu==1){
			GoTo(52,13);
			DoiMau(0,11);
    		printf("  BAT DAU");
		}
		if(choncu==3){
			GoTo(52,15);
			DoiMau(0,11);
    		printf("   KY LUC");	
		}
		GoTo(51,14);
		DoiMau(0,9);
		printf("%c LUAT CHOI",16);
		DoiMau(0,11);
	}
    //3=> 2->3 hoặc 4->3
	if(chon==3){
		if(choncu==2){
			GoTo(51,14);
			DoiMau(0,11);
    		printf("  LUAT CHOI");	
		}
		if(choncu==4){
			GoTo(49,16);
			DoiMau(0,11);
    		printf("  THONG TIN GAME ");	
		}
		GoTo(52,15);
		DoiMau(0,9);
		printf("%c  KY LUC",16);
		DoiMau(0,11);
	}
    //4=> 3->4 
	if(chon==4){
		if(choncu==3){
			GoTo(52,15);
			DoiMau(0,11);
    		printf("   KY LUC");	
		}
		GoTo(49,16);
		DoiMau(0,9);
		printf("%c THONG TIN GAME ",16);
		DoiMau(0,11);
	}
}
//Ham hien thi vat pham
void HienThi(){
	GoTo(0,31);
	printf("HP: %c %c %c %c %c",3,3,3,3,3);
	int j=12;
	while(j>((HP+1)*2)){
		GoTo(j,31);
		printf(" ");
		j-=2;
	}
	GoTo(20,31);
	printf("Chia khoa: ");
	for(int i=1; i<=DemCK; i++){
		printf("%c ",42);
	}
}
//Ham ket thuc
void end(){
	if(HP==0){
		system("cls");
		GhiThoiGian(10000);
		GoTo(52,13);
		printf("BAN DA THUA");
		GoTo(56,14);
		printf(":((");
		GoTo(0,27);
		printf("ESC: quay lai menu   ENTER: choi lai");
		while(1){
			char phim=getch();
			if(phim==27){
				Menu();
			}
			if(phim==13){
				if(MChoi==1){
					Man_1();
				}
				if(MChoi==2){
					Man_2();
				}
				if(MChoi==3){
					Man_3();
				}
			}
		}	
	}
	if(CheckCua==true){
		if(MChoi==3){
			time(&GhiNV.t2);
			Outro();
			system("cls");
			GoTo(50,13);
			printf("XIN CHUC MUNG!!!");
			GoTo(38,14);
			printf("BAN DA HOAN THANH MAN CHOI VOI KI LUC: %.3f",difftime(GhiNV.t2,GhiNV.t1));
			GoTo(0,27);
			printf("ESC: quay lai menu");
			GhiThoiGian(difftime(GhiNV.t2,GhiNV.t1));
			while(1){
				char phim=getch();
				if(phim==27){
					Menu();
				}
			}
		}
		system("cls");
		GoTo(50,13);
		printf("XIN CHUC MUNG!!!");
		GoTo(44,14);
		printf("BAN DA HOAN THANH MAN CHOI");
		GoTo(0,27);
		printf("ESC: quay lai menu   ENTER: man tiep theo");
		while(1){
			char phim=getch();
			if(phim==27){
				Menu();
			}
			if(phim==13){
				if(MChoi==1){
					Man_2();
				}
				if(MChoi==2){
					Man_3();
				}
			}
		}	
	}
}


//Ham reset lai cac thong so
void Reset(){
	for(int i=0; i<=1610; i++){
		Map[i].VT.x=0;
		Map[i].VT.y=0;
		Map[i].kt=0;
	}
	for(int i=0; i<=500; i++){
		Gai[i].VT.x=0;
		Gai[i].VT.y=0;
		Gai[i].kt=0;
	}
	for(int i=0; i<=50; i++){
		ThangL[i].VT.x=0;
		ThangL[i].VT.y=0;
		ThangL[i].kt=0;
	}
	for(int i=0; i<=50; i++){
		CuaChan[i].VT.x=0;
		CuaChan[i].VT.y=0;
		CuaChan[i].kt=0;
	}
	for(int i=0; i<=10; i++){
		CK[i].x=0; CK[i].y=0;
		Cua[i].x=0; Cua[i].y=0;
		GaiQL[i].x=0; GaiQL[i].y=0;
		ThangLDen[i].x=0; ThangLDen[i].y=0;
		ThangLDi[i].x=0; ThangLDi[i].y=0;
		KhoiDat[i].x=0; KhoiDat[i].y=0;
		CTac[i].x=0; CTac[i].y=0;
	}
	HP=5;	//Mau cua nhan vat
	DM=0;	//Bien dem de ghi toa do dat
	DemCK=0;	//Bien dem so luong chia khoa nhan vat dang co
	DemGai=0;	//Bien dem so luong gai trong map
	GQL=0;	//Bien chi dinhj vi tri qua lai khi trug gai
	DemTL=0;	//Bien dem so luong bac thang co trong map
	TDvaD=0;	//Bieen chi dinh vi tri den va di khi leo thang
	DemKD=0;	//Bien dem so luong khoi dat trong map
	hD=0;	//Huong di chuyen cua nhan vat  1:phai  -1:trai
	hR=0;
	DemCT=0;	//Bien dem so cong tac tren map
	DemCC=0;	//Bien dem so luong cua chan cos tren map
	CheckCua=false;	//Huong roi cua nhan vat
}

//Man chơi
void Man_1(){
	MChoi=1;
	Reset();
	Map_1(219);
	NV(nv.x,nv.y);
	DieuKhien(nv.x,nv.y);
}
void Man_2(){
	MChoi=2;
	Reset();
	Map_2(219);
	NV(nv.x,nv.y);
	DieuKhien(nv.x,nv.y);
}
void Man_3(){
	MChoi=3;
	Reset();
	Map_3(219);
	NV(nv.x,nv.y);
	DieuKhien(nv.x,nv.y);
}

//INTRO GAME (THE RIVER)
void Intro(){
	system("cls");
	char enter;
	HChuT();
	HChuH();
	HChuE();
	HChuR();
	HChuI();
	HChuV();
	HChuE2();
	HChuR2();
	Sleep(500);
	while(1){
		if(kbhit()){
			enter=getch();
			if(enter==13)
				break;
		}
		Sleep(200);
		HIntro();
		Sleep(200);
		AIntro();
		Sleep(200);
		HIntro();
		Sleep(200);
		AIntro();
		Sleep(200);
		HIntro();
		Sleep(200);
		AIntro();
		Sleep(90);
		HIntro();
		Sleep(90);
		AIntro();
		Sleep(90);
		HIntro();
		Sleep(90);
		AIntro();
		Sleep(90);
		HIntro();
		Sleep(800);
	}
}
void HChuT(){
	DoiMau(0,9);
	char x=219; 
	for (int i=25; i<=32; i++){
		GoTo(i,11);
		Sleep(20);
		printf("%c",x);
	}
	for (int i=12; i<=15; i++){
		GoTo(28,i);
		Sleep(20);
		printf("%c",x);
	}
	for (int i=12; i<=15; i++){
		GoTo(29,i);
		Sleep(20);
		printf("%c",x);
	}
	GoTo(25,12); 
	Sleep(20);
	printf("%c",200);
	GoTo(26,12); 
	Sleep(20);
	printf("%c",205);
	GoTo(27,12); 
	Sleep(20);
	printf("%c",205);
	GoTo(33,11);
	Sleep(20);
	printf("%c", 187);
	GoTo(33,12);
	Sleep(20);
	printf("%c", 188);
	GoTo(31,12);
	Sleep(20);
	printf("%c", 205);
	GoTo(32,12);
	Sleep(20);
	printf("%c", 205);
	GoTo(30,12);
	Sleep(20);
	printf("%c", 201);
	GoTo(30,13);
	Sleep(20);
	printf("%c", 186);
	GoTo(30,14);
	Sleep(20);
	printf("%c", 186);
	GoTo(30,15);
	Sleep(20);
	printf("%c", 186);
	GoTo(30,16);
	Sleep(20);
	printf("%c", 188);
	GoTo(29,16);
	Sleep(20);
	printf("%c", 205);
	GoTo(28,16);
	Sleep(20);
	printf("%c", 200);
}
void HChuH(){
	DoiMau(0,9);
	char x=219; 
	for(int i=11; i<=15; i++){
		GoTo(34,i);
		Sleep(20);
		printf("%c",x);
	}
	for(int i=11; i<=15; i++){
		GoTo(35,i);
		Sleep(20);
		printf("%c",x);
	}
	for(int i=36; i<=38; i++){
		GoTo(i,13);
		Sleep(20);
		printf("%c",x);
	}
	for(int i=11; i<=15; i++){
		GoTo(39,i);
		Sleep(20);
		printf("%c",x);
	}
	for(int i=11; i<=15; i++){
		GoTo(40,i);
		Sleep(20);
		printf("%c",x);
	}
	GoTo(36,11);
	Sleep(20);
	printf("%c", 187);
	GoTo(36,12);
	Sleep(20);
	printf("%c", 186);
	GoTo(36,14);
	Sleep(20);
	printf("%c", 201);
	GoTo(37,14);
	Sleep(20);
	printf("%c", 205);
	GoTo(38,14);
	Sleep(20);
	printf("%c", 205);
	GoTo(36,15);
	Sleep(20);
	printf("%c", 186);
	GoTo(36,16);
	Sleep(20);
	printf("%c", 188);
	GoTo(35,16);
	Sleep(20);
	printf("%c", 205);
	GoTo(34,16);
	Sleep(20);
	printf("%c", 200);
	GoTo(41,11);
	Sleep(20);
	printf("%c", 187);
	GoTo(41,12);
	Sleep(20);
	printf("%c", 186);
	GoTo(41,13);
	Sleep(20);
	printf("%c", 186);
	GoTo(41,14);
	Sleep(20);
	printf("%c", 186);
	GoTo(41,15);
	Sleep(20);
	printf("%c", 186);
	GoTo(41,16);
	Sleep(20);
	printf("%c", 188);
	GoTo(40,16);
	Sleep(20);
	printf("%c", 205);
	GoTo(39,16);
	Sleep(20);
	printf("%c", 200);
}
void HChuE(){
	DoiMau(0,9);
	char x=219;
	for (int i=42; i<=48; i++){
		GoTo(i,11);
		Sleep(20);
		printf("%c",x);
	}
	for (int i=12; i<=14; i++){
		GoTo(42,i);
		Sleep(20);
		printf("%c",x);
	}
	for (int i=12; i<=14; i++){
		GoTo(43,i);
		Sleep(20);
		printf("%c",x);
	}
	for (int i=42; i<=48; i++){
		GoTo(i,15);
		Sleep(20);
		printf("%c",x);
	}
	for (int i=44; i<=46; i++){
		GoTo(i,13);
		Sleep(20);
		printf("%c",x);
	}
	GoTo(49,11);
	Sleep(20);
	printf("%c",187);
	GoTo(49,12);
	Sleep(20);
	printf("%c",188);
	GoTo(48,12);
	Sleep(20);
	printf("%c",205);
	GoTo(48,12);
	Sleep(20);
	printf("%c",205);
	GoTo(47,12);
	Sleep(20);
	printf("%c",205);
	GoTo(46,12);
	Sleep(20);
	printf("%c",205);
	GoTo(45,12);
	Sleep(20);
	printf("%c",205);
	GoTo(44,12);
	Sleep(20);
	printf("%c",201);
	GoTo(47,13);
	Sleep(20);
	printf("%c",187);
	GoTo(47,14);
	Sleep(20);
	printf("%c",188);
	GoTo(46,14);
	Sleep(20);
	printf("%c",205);
	GoTo(45,14);
	Sleep(20);
	printf("%c",205);
	GoTo(44,14);
	Sleep(20);
	printf("%c",201);
	GoTo(49,15);
	Sleep(20);
	printf("%c",187);
	GoTo(49,16);
	Sleep(20);
	printf("%c",188);
	GoTo(48,16);
	Sleep(20);
	printf("%c",205);
	GoTo(47,16);
	Sleep(20);
	printf("%c",205);
	GoTo(46,16);
	Sleep(20);
	printf("%c",205);
	GoTo(45,16);
	Sleep(20);
	printf("%c",205);
	GoTo(44,16);
	Sleep(20);
	printf("%c",205);
	GoTo(43,16);
	Sleep(20);
	printf("%c",205);
	GoTo(42,16);
	Sleep(20);
	printf("%c",200);
}
void HChuI(){
	DoiMau(0,9);
	char x=219;
	for (int i=11; i<=15; i++){
		GoTo(62,i);
		Sleep(20);
		printf("%c",x);
	}
	for (int i=11; i<=15; i++){
		GoTo(63,i);
		Sleep(20);
		printf("%c",x);
	}
	GoTo(64,11);
	Sleep(20);
	printf("%c",187);
	GoTo(64,12);
	Sleep(20);
	printf("%c",186);
	GoTo(64,13);
	Sleep(20);
	printf("%c",186);
	GoTo(64,14);
	Sleep(20);
	printf("%c",186);
	GoTo(64,15);
	Sleep(20);
	printf("%c",186);
	GoTo(64,16);
	Sleep(20);
	printf("%c",188);
	GoTo(63,16);
	Sleep(20);
	printf("%c",205);
	GoTo(62,16);
	Sleep(20);
	printf("%c",200);
}
void HChuR(){
	DoiMau(0,9);
	char x=219;
	for (int i=11; i<=15; i++){
		GoTo(54,i);
		Sleep(20);
		printf("%c",x);
	}
	for (int i=11; i<=15; i++){
		GoTo(55,i);
		Sleep(20);
		printf("%c",x);
	}
	for (int i=56; i<=59; i++){
		GoTo(i,11);
		Sleep(20);
		printf("%c",x);
	}
	GoTo(59,12);
	Sleep(20);
	printf("%c",x);
	GoTo(60,12);
	Sleep(20);
	printf("%c",x);
	for (int i=56; i<=59; i++){
		GoTo(i,13);
		Sleep(20);
		printf("%c",x);
	}
	GoTo(59,14);
	Sleep(20);
	printf("%c",x);
	GoTo(59,15);
	Sleep(20);
	printf("%c",x);
	GoTo(60,14);
	Sleep(20);
	printf("%c",x);
	GoTo(60,15);
	Sleep(20);
	printf("%c",x);
	GoTo(60,11);
	Sleep(20);
	printf("%c",187);	
	GoTo(61,12);
	Sleep(20);
	printf("%c",187);	
	GoTo(61,13);
	Sleep(20);
	printf("%c",188);	
	GoTo(60,13);
	Sleep(20);
	printf("%c",201);
	GoTo(61,14);
	Sleep(20);
	printf("%c",187);
	GoTo(61,15);
	Sleep(20);
	printf("%c",186);
	GoTo(61,16);
	Sleep(20);
	printf("%c",188);
	GoTo(60,16);
	Sleep(20);
	printf("%c",205);
	GoTo(59,16);
	Sleep(20);
	printf("%c",200);
	GoTo(56,12);
	Sleep(20);
	printf("%c",201);
	GoTo(57,12);
	Sleep(20);
	printf("%c",205);
	GoTo(58,12);
	Sleep(20);
	printf("%c",205);
	GoTo(56,14);
	Sleep(20);
	printf("%c",201);
	GoTo(57,14);
	Sleep(20);
	printf("%c",205);
	GoTo(58,14);
	Sleep(20);
	printf("%c",205);
	GoTo(56,15);
	Sleep(20);
	printf("%c",186);
	GoTo(56,16);
	Sleep(20);
	printf("%c",188);
	GoTo(55,16);
	Sleep(20);
	printf("%c",205);
	GoTo(54,16);
	Sleep(20);
	printf("%c",200);
}
void HChuV(){
	DoiMau(0,9);
	char x=219;
	for (int i=11; i<=13; i++){
		GoTo(65,i);
		Sleep(20);
		printf("%c",x);
	}
	for (int i=11; i<=14; i++){
		GoTo(66,i);
		Sleep(20);
		printf("%c",x);
	}
	GoTo(67,14);
	Sleep(20);
	printf("%c",x);
	for (int i=67; i<=70; i++){
		GoTo(i,15);
		Sleep(20);
		printf("%c",x);
	}
	
	for (int i=11; i<=13; i++){
		GoTo(72,i);
		Sleep(20);
		printf("%c",x);
	}
	for (int i=11; i<=14; i++){
		GoTo(71,i);
		Sleep(20);
		printf("%c",x);
	}
	GoTo(70,14);
	Sleep(20);
	printf("%c",x);
	GoTo(67,11);
	Sleep(20);
	printf("%c",187);
	GoTo(67,12);
	Sleep(20);
	printf("%c",186);
	GoTo(67,13);
	Sleep(20);
	printf("%c",186);
	GoTo(68,14);
	Sleep(20);
	printf("%c",187);
	GoTo(65,14);
	Sleep(20);
	printf("%c",200);
	GoTo(66,15);
	Sleep(20);
	printf("%c",200);
	GoTo(67,16);
	Sleep(20);
	printf("%c",200);
	GoTo(68,16);
	Sleep(20);
	printf("%c",205);
	GoTo(69,16);
	Sleep(20);
	printf("%c",205);
	GoTo(70,16);
	Sleep(20);
	printf("%c",205);
	GoTo(71,16);
	Sleep(20);
	printf("%c",188);
	GoTo(71,15);
	Sleep(20);
	printf("%c",201);
	GoTo(72,15);
	Sleep(20);
	printf("%c",188);
	GoTo(72,14);
	Sleep(20);
	printf("%c",201);
	GoTo(73,14);
	Sleep(20);
	printf("%c",188);
	GoTo(73,13);
	Sleep(20);
	printf("%c",186);
	GoTo(73,12);
	Sleep(20);
	printf("%c",186);
	GoTo(73,11);
	Sleep(20);
	printf("%c",187);
}
void HChuE2(){
	DoiMau(0,9);
	char x=219;
	for (int i=74; i<=80; i++){
		GoTo(i,11);
		Sleep(20);
		printf("%c",x);
	}
	for (int i=12; i<=15; i++){
		GoTo(74,i);
		Sleep(20);
		printf("%c",x);
	}
	for (int i=12; i<=15; i++){
		GoTo(75,i);
		Sleep(20);
		printf("%c",x);
	}
	for (int i=76; i<=80; i++){
		GoTo(i,15);
		Sleep(20);
		printf("%c",x);
	}
	for (int i=76; i<=78; i++){
		GoTo(i,13);
		Sleep(20);
		printf("%c",x);
	}
	GoTo(81,11);
	Sleep(20);
	printf("%c",187);
	GoTo(81,12);
	Sleep(20);
	printf("%c",188);
	GoTo(80,12);
	Sleep(20);
	printf("%c",205);
	GoTo(80,12);
	Sleep(20);
	printf("%c",205);
	GoTo(79,12);
	Sleep(20);
	printf("%c",205);
	GoTo(78,12);
	Sleep(20);
	printf("%c",205);
	GoTo(77,12);
	Sleep(20);
	printf("%c",205);
	GoTo(76,12);
	Sleep(20);
	printf("%c",201);
	GoTo(79,13);
	Sleep(20);
	printf("%c",187);
	GoTo(79,14);
	Sleep(20);
	printf("%c",188);
	GoTo(78,14);
	Sleep(20);
	printf("%c",205);
	GoTo(77,14);
	Sleep(20);
	printf("%c",205);
	GoTo(76,14);
	Sleep(20);
	printf("%c",201);
	GoTo(81,15);
	Sleep(20);
	printf("%c",187);
	GoTo(81,16);
	Sleep(20);
	printf("%c",188);
	GoTo(80,16);
	Sleep(20);
	printf("%c",205);
	GoTo(79,16);
	Sleep(20);
	printf("%c",205);
	GoTo(78,16);
	Sleep(20);
	printf("%c",205);
	GoTo(77,16);
	Sleep(20);
	printf("%c",205);
	GoTo(76,16);
	Sleep(20);
	printf("%c",205);
	GoTo(75,16);
	Sleep(20);
	printf("%c",205);
	GoTo(74,16);
	Sleep(20);
	printf("%c",200);
}
void HChuR2(){
	DoiMau(0,9);
	char x=219;
	for (int i=11; i<=15; i++){
		GoTo(82,i);
		Sleep(20);
		printf("%c",x);
	}
	for (int i=11; i<=15; i++){
		GoTo(83,i);
		Sleep(20);
		printf("%c",x);
	}
	for (int i=84; i<=87; i++){
		GoTo(i,11);
		Sleep(20);
		printf("%c",x);
	}
	GoTo(87,12);
	Sleep(20);
	printf("%c",x);
	GoTo(88,12);
	Sleep(20);
	printf("%c",x);
	for (int i=84; i<=87; i++){
		GoTo(i,13);
		Sleep(20);
		printf("%c",x);
	}
	GoTo(87,14);
	Sleep(20);
	printf("%c",x);
	GoTo(87,15);
	Sleep(20);
	printf("%c",x);
	GoTo(88,14);
	Sleep(20);
	printf("%c",x);
	GoTo(88,15);
	Sleep(20);
	printf("%c",x);
	GoTo(88,11);
	Sleep(20);
	printf("%c",187);	
	GoTo(89,12);
	Sleep(20);
	printf("%c",187);	
	GoTo(89,13);
	Sleep(20);
	printf("%c",188);	
	GoTo(88,13);
	Sleep(20);
	printf("%c",201);
	GoTo(89,14);
	Sleep(20);
	printf("%c",187);
	GoTo(89,15);
	Sleep(20);
	printf("%c",186);
	GoTo(89,16);
	Sleep(20);
	printf("%c",188);
	GoTo(88,16);
	Sleep(20);
	printf("%c",205);
	GoTo(87,16);
	Sleep(20);
	printf("%c",200);
	GoTo(86,12);
	Sleep(20);
	printf("%c",201);
	GoTo(85,12);
	Sleep(20);
	printf("%c",205);
	GoTo(86,12);
	Sleep(20);
	printf("%c",205);
	GoTo(84,14);
	Sleep(20);
	printf("%c",201);
	GoTo(85,14);
	Sleep(20);
	printf("%c",205);
	GoTo(86,14);
	Sleep(20);
	printf("%c",205);
	GoTo(84,15);
	Sleep(20);
	printf("%c",186);
	GoTo(84,16);
	Sleep(20);
	printf("%c",188);
	GoTo(83,16);
	Sleep(20);
	printf("%c",205);
	GoTo(82,16);
	Sleep(20);
	printf("%c",200);
}
void HIntro(){
	DoiMau(0,9);
	char x=219; 
	//chu T
	for (int i=25; i<=32; i++){
		GoTo(i,11);
		printf("%c",x);
	}
	for (int i=12; i<=15; i++){
		GoTo(28,i);
		printf("%c",x);
	}
	for (int i=12; i<=15; i++){
		GoTo(29,i);
		printf("%c",x);
	}
	GoTo(25,12); 
	printf("%c",200);
	GoTo(26,12); 
	printf("%c",205);
	GoTo(27,12); 
	printf("%c",205);
	GoTo(33,11);
	printf("%c", 187);
	GoTo(33,12);
	printf("%c", 188);
	GoTo(31,12);
	printf("%c", 205);
	GoTo(32,12);
	printf("%c", 205);
	GoTo(30,12);
	printf("%c", 201);
	GoTo(30,13);
	printf("%c", 186);
	GoTo(30,14);
	printf("%c", 186);
	GoTo(30,15);
	printf("%c", 186);
	GoTo(30,16);
	printf("%c", 188);
	GoTo(29,16);
	printf("%c", 205);
	GoTo(28,16);
	printf("%c", 200);
//Chu H
	for(int i=11; i<=15; i++){
		GoTo(34,i);
		printf("%c",x);
	}
	for(int i=11; i<=15; i++){
		GoTo(35,i);
		printf("%c",x);
	}
	for(int i=36; i<=38; i++){
		GoTo(i,13);
		printf("%c",x);
	}
	for(int i=11; i<=15; i++){
		GoTo(39,i);
		printf("%c",x);
	}
	for(int i=11; i<=15; i++){
		GoTo(40,i);
		printf("%c",x);
	}
	GoTo(36,11);
	printf("%c", 187);
	GoTo(36,12);
	printf("%c", 186);
	GoTo(36,14);
	printf("%c", 201);
	GoTo(37,14);
	printf("%c", 205);
	GoTo(38,14);
	printf("%c", 205);
	GoTo(36,15);
	printf("%c", 186);
	GoTo(36,16);
	printf("%c", 188);
	GoTo(35,16);
	printf("%c", 205);
	GoTo(34,16);
	printf("%c", 200);
	GoTo(41,11);
	printf("%c", 187);
	GoTo(41,12);
	printf("%c", 186);
	GoTo(41,13);
	printf("%c", 186);
	GoTo(41,14);
	printf("%c", 186);
	GoTo(41,15);
	printf("%c", 186);
	GoTo(41,16);
	printf("%c", 188);
	GoTo(40,16);
	printf("%c", 205);
	GoTo(39,16);
	printf("%c", 200);
//Chu E
	for (int i=42; i<=48; i++){
		GoTo(i,11);
		printf("%c",x);
	}
	for (int i=12; i<=14; i++){
		GoTo(42,i);
		printf("%c",x);
	}
	for (int i=12; i<=14; i++){
		GoTo(43,i);
		printf("%c",x);
	}
	for (int i=42; i<=48; i++){
		GoTo(i,15);
		printf("%c",x);
	}
	for (int i=44; i<=46; i++){
		GoTo(i,13);
		printf("%c",x);
	}
	GoTo(49,11);
	printf("%c",187);
	GoTo(49,12);
	printf("%c",188);
	GoTo(48,12);
	printf("%c",205);
	GoTo(48,12);
	printf("%c",205);
	GoTo(47,12);
	printf("%c",205);
	GoTo(46,12);
	printf("%c",205);
	GoTo(45,12);
	printf("%c",205);
	GoTo(44,12);
	printf("%c",201);
	GoTo(47,13);
	printf("%c",187);
	GoTo(47,14);
	printf("%c",188);
	GoTo(46,14);
	printf("%c",205);
	GoTo(45,14);
	printf("%c",205);
	GoTo(44,14);
	printf("%c",201);
	GoTo(49,15);
	printf("%c",187);
	GoTo(49,16);
	printf("%c",188);
	GoTo(48,16);
	printf("%c",205);
	GoTo(47,16);
	printf("%c",205);
	GoTo(46,16);
	printf("%c",205);
	GoTo(45,16);
	printf("%c",205);
	GoTo(44,16);
	printf("%c",205);
	GoTo(43,16);
	printf("%c",205);
	GoTo(42,16);
	printf("%c",200);
//Chu R
	for (int i=11; i<=15; i++){
		GoTo(54,i);
		printf("%c",x);
	}
	for (int i=11; i<=15; i++){
		GoTo(55,i);
		printf("%c",x);
	}
	for (int i=56; i<=59; i++){
		GoTo(i,11);
		printf("%c",x);
	}
	GoTo(59,12);
	printf("%c",x);
	GoTo(60,12);
	printf("%c",x);
	for (int i=56; i<=59; i++){
		GoTo(i,13);
		printf("%c",x);
	}
	GoTo(59,14);
	printf("%c",x);
	GoTo(59,15);
	printf("%c",x);
	GoTo(60,14);
	printf("%c",x);
	GoTo(60,15);
	printf("%c",x);
	GoTo(60,11);
	printf("%c",187);	
	GoTo(61,12);
	printf("%c",187);	
	GoTo(61,13);
	printf("%c",188);	
	GoTo(60,13);
	printf("%c",201);
	GoTo(61,14);
	printf("%c",187);
	GoTo(61,15);
	printf("%c",186);
	GoTo(61,16);
	printf("%c",188);
	GoTo(60,16);
	printf("%c",205);
	GoTo(59,16);
	printf("%c",200);
	GoTo(56,12);
	printf("%c",201);
	GoTo(57,12);
	printf("%c",205);
	GoTo(58,12);
	printf("%c",205);
	GoTo(56,14);
	printf("%c",201);
	GoTo(57,14);
	printf("%c",205);
	GoTo(58,14);
	printf("%c",205);
	GoTo(56,15);
	printf("%c",186);
	GoTo(56,16);
	printf("%c",188);
	GoTo(55,16);
	printf("%c",205);
	GoTo(54,16);
	printf("%c",200);
//Chu I
	for (int i=11; i<=15; i++){
		GoTo(62,i);
		printf("%c",x);
	}
	for (int i=11; i<=15; i++){
		GoTo(63,i);
		printf("%c",x);
	}
	GoTo(64,11);
	printf("%c",187);
	GoTo(64,12);
	printf("%c",186);
	GoTo(64,13);
	printf("%c",186);
	GoTo(64,14);
	printf("%c",186);
	GoTo(64,15);
	printf("%c",186);
	GoTo(64,16);
	printf("%c",188);
	GoTo(63,16);
	printf("%c",205);
	GoTo(62,16);
	printf("%c",200);
//Chu V
	for (int i=11; i<=13; i++){
		GoTo(65,i);
		printf("%c",x);
	}
	for (int i=11; i<=14; i++){
		GoTo(66,i);
		printf("%c",x);
	}
	GoTo(67,14);
	printf("%c",x);
	for (int i=67; i<=70; i++){
		GoTo(i,15);
		printf("%c",x);
	}
	
	for (int i=11; i<=13; i++){
		GoTo(72,i);
		printf("%c",x);
	}
	for (int i=11; i<=14; i++){
		GoTo(71,i);
		printf("%c",x);
	}
	GoTo(70,14);
	printf("%c",x);
	GoTo(67,11);
	printf("%c",187);
	GoTo(67,12);
	printf("%c",186);
	GoTo(67,13);
	printf("%c",186);
	GoTo(68,14);
	printf("%c",187);
	GoTo(65,14);
	printf("%c",200);
	GoTo(66,15);
	printf("%c",200);
	GoTo(67,16);
	printf("%c",200);
	GoTo(68,16);
	printf("%c",205);
	GoTo(69,16);
	printf("%c",205);
	GoTo(70,16);
	printf("%c",205);
	GoTo(71,16);
	printf("%c",188);
	GoTo(71,15);
	printf("%c",201);
	GoTo(72,15);
	printf("%c",188);
	GoTo(72,14);
	printf("%c",201);
	GoTo(73,14);
	printf("%c",188);
	GoTo(73,13);
	printf("%c",186);
	GoTo(73,12);
	printf("%c",186);
	GoTo(73,11);
	printf("%c",187);
//Chu E2
	for (int i=74; i<=80; i++){
		GoTo(i,11);
		printf("%c",x);
	}
	for (int i=12; i<=15; i++){
		GoTo(74,i);
		printf("%c",x);
	}
	for (int i=12; i<=15; i++){
		GoTo(75,i);
		printf("%c",x);
	}
	for (int i=76; i<=80; i++){
		GoTo(i,15);
		printf("%c",x);
	}
	for (int i=76; i<=78; i++){
		GoTo(i,13);
		printf("%c",x);
	}
	GoTo(81,11);
	printf("%c",187);
	GoTo(81,12);
	printf("%c",188);
	GoTo(80,12);
	printf("%c",205);
	GoTo(80,12);
	printf("%c",205);
	GoTo(79,12);
	printf("%c",205);
	GoTo(78,12);
	printf("%c",205);
	GoTo(77,12);
	printf("%c",205);
	GoTo(76,12);
	printf("%c",201);
	GoTo(79,13);
	printf("%c",187);
	GoTo(79,14);
	printf("%c",188);
	GoTo(78,14);
	printf("%c",205);
	GoTo(77,14);
	printf("%c",205);
	GoTo(76,14);
	printf("%c",201);
	GoTo(81,15);
	printf("%c",187);
	GoTo(81,16);
	printf("%c",188);
	GoTo(80,16);
	printf("%c",205);
	GoTo(79,16);
	printf("%c",205);
	GoTo(78,16);
	printf("%c",205);
	GoTo(77,16);
	printf("%c",205);
	GoTo(76,16);
	printf("%c",205);
	GoTo(75,16);
	printf("%c",205);
	GoTo(74,16);
	printf("%c",200);
//Chu R2
	for (int i=11; i<=15; i++){
		GoTo(82,i);
		printf("%c",x);
	}
	for (int i=11; i<=15; i++){
		GoTo(83,i);
		printf("%c",x);
	}
	for (int i=84; i<=87; i++){
		GoTo(i,11);
		printf("%c",x);
	}
	GoTo(87,12);
	printf("%c",x);
	GoTo(88,12);
	printf("%c",x);
	for (int i=84; i<=87; i++){
		GoTo(i,13);
		printf("%c",x);
	}
	GoTo(87,14);
	printf("%c",x);
	GoTo(87,15);
	printf("%c",x);
	GoTo(88,14);
	printf("%c",x);
	GoTo(88,15);
	printf("%c",x);
	GoTo(88,11);
	printf("%c",187);	
	GoTo(89,12);
	printf("%c",187);	
	GoTo(89,13);
	printf("%c",188);	
	GoTo(88,13);
	printf("%c",201);
	GoTo(89,14);
	printf("%c",187);
	GoTo(89,15);
	printf("%c",186);
	GoTo(89,16);
	printf("%c",188);
	GoTo(88,16);
	printf("%c",205);
	GoTo(87,16);
	printf("%c",200);
	GoTo(86,12);
	printf("%c",201);
	GoTo(85,12);
	printf("%c",205);
	GoTo(86,12);
	printf("%c",205);
	GoTo(84,14);
	printf("%c",201);
	GoTo(85,14);
	printf("%c",205);
	GoTo(86,14);
	printf("%c",205);
	GoTo(84,15);
	printf("%c",186);
	GoTo(84,16);
	printf("%c",188);
	GoTo(83,16);
	printf("%c",205);
	GoTo(82,16);
	printf("%c",200);


	GoTo(1,27);
	printf ("%s", "Nhan Enter de tiep tuc");
	// char enter;
	// while(1){
	// 		enter=getch();
	// 		if(enter==13)
	// 			break;
	// 	}
	//	Menu();
}
void AIntro(){
	DoiMau(0,9);
	char x=219; 
	//chu T
	for (int i=25; i<=32; i++){
		GoTo(i,11);
		printf(" ");
	}
	for (int i=12; i<=15; i++){
		GoTo(28,i);
		printf(" ");
	}
	for (int i=12; i<=15; i++){
		GoTo(29,i);
		printf(" ");
	}
	GoTo(25,12); 
	printf(" ");
	GoTo(26,12); 
	printf(" ");
	GoTo(27,12); 
	printf(" ");
	GoTo(33,11);
	printf(" ");
	GoTo(33,12);
	printf(" ");
	GoTo(31,12);
	printf(" ");
	GoTo(32,12);
	printf(" ");
	GoTo(30,12);
	printf(" ");
	GoTo(30,13);
	printf(" ");
	GoTo(30,14);
	printf(" ");
	GoTo(30,15);
	printf(" ");
	GoTo(30,16);
	printf(" ");
	GoTo(29,16);
	printf(" ");
	GoTo(28,16);
	printf(" ");
	//Chu H
	for(int i=11; i<=15; i++){
		GoTo(34,i);
		printf(" ");
	}
	for(int i=11; i<=15; i++){
		GoTo(35,i);
		printf(" ");
	}
	for(int i=36; i<=38; i++){
		GoTo(i,13);
		printf(" ");
	}
	for(int i=11; i<=15; i++){
		GoTo(39,i);
		printf(" ");
	}
	for(int i=11; i<=15; i++){
		GoTo(40,i);
		printf(" ");
	}
	GoTo(36,11);
	printf(" ");
	GoTo(36,12);
	printf(" ");
	GoTo(36,14);
	printf(" ");
	GoTo(37,14);
	printf(" ");
	GoTo(38,14);
	printf(" ");
	GoTo(36,15);
	printf(" ");
	GoTo(36,16);
	printf(" ");
	GoTo(35,16);
	printf(" ");
	GoTo(34,16);
	printf(" ");
	GoTo(41,11);
	printf(" ");
	GoTo(41,12);
	printf(" ");
	GoTo(41,13);
	printf(" ");
	GoTo(41,14);
	printf(" ");
	GoTo(41,15);
	printf(" ");
	GoTo(41,16);
	printf(" ");
	GoTo(40,16);
	printf(" ");
	GoTo(39,16);
	printf(" ");
//Chu E
	for (int i=42; i<=48; i++){
		GoTo(i,11);
		printf(" ");
	}
	for (int i=12; i<=14; i++){
		GoTo(42,i);
		printf(" ");
	}
	for (int i=12; i<=14; i++){
		GoTo(43,i);
		printf(" ");
	}
	for (int i=42; i<=48; i++){
		GoTo(i,15);
		printf(" ");
	}
	for (int i=44; i<=46; i++){
		GoTo(i,13);
		printf(" ");
	}
	GoTo(49,11);
	printf(" ");
	GoTo(49,12);
	printf(" ");
	GoTo(48,12);
	printf(" ");
	GoTo(48,12);
	printf(" ");
	GoTo(47,12);
	printf(" ");
	GoTo(46,12);
	printf(" ");
	GoTo(45,12);
	printf(" ");
	GoTo(44,12);
	printf(" ");
	GoTo(47,13);
	printf(" ");
	GoTo(47,14);
	printf(" ");
	GoTo(46,14);
	printf(" ");
	GoTo(45,14);
	printf(" ");
	GoTo(44,14);
	printf(" ");
	GoTo(49,15);
	printf(" ");
	GoTo(49,16);
	printf(" ");
	GoTo(48,16);
	printf(" ");
	GoTo(47,16);
	printf(" ");
	GoTo(46,16);
	printf(" ");
	GoTo(45,16);
	printf(" ");
	GoTo(44,16);
	printf(" ");
	GoTo(43,16);
	printf(" ");
	GoTo(42,16);
	printf(" ");
//Chu R
	for (int i=11; i<=15; i++){
		GoTo(54,i);
		printf(" ");
	}
	for (int i=11; i<=15; i++){
		GoTo(55,i);
		printf(" ");
	}
	for (int i=56; i<=59; i++){
		GoTo(i,11);
		printf(" ");
	}
	GoTo(59,12);
	printf(" ");
	GoTo(60,12);
	printf(" ");
	for (int i=56; i<=59; i++){
		GoTo(i,13);
		printf(" ");
	}
	GoTo(59,14);
	printf(" ");
	GoTo(59,15);
	printf(" ");
	GoTo(60,14);
	printf(" ");
	GoTo(60,15);
	printf(" ");
	GoTo(60,11);
	printf(" ");	
	GoTo(61,12);
	printf(" ");	
	GoTo(61,13);
	printf(" ");	
	GoTo(60,13);
	printf(" ");
	GoTo(61,14);
	printf(" ");
	GoTo(61,15);
	printf(" ");
	GoTo(61,16);
	printf(" ");
	GoTo(60,16);
	printf(" ");
	GoTo(59,16);
	printf(" ");
	GoTo(56,12);
	printf(" ");
	GoTo(57,12);
	printf(" ");
	GoTo(58,12);
	printf(" ");
	GoTo(56,14);
	printf(" ");
	GoTo(57,14);
	printf(" ");
	GoTo(58,14);
	printf(" ");
	GoTo(56,15);
	printf(" ");
	GoTo(56,16);
	printf(" ");
	GoTo(55,16);
	printf(" ");
	GoTo(54,16);
	printf(" ");
//Chu I
	for (int i=11; i<=15; i++){
		GoTo(62,i);
		printf(" ");
	}
	for (int i=11; i<=15; i++){
		GoTo(63,i);
		printf(" ");
	}
	GoTo(64,11);
	printf(" ");
	GoTo(64,12);
	printf(" ");
	GoTo(64,13);
	printf(" ");
	GoTo(64,14);
	printf(" ");
	GoTo(64,15);
	printf(" ");
	GoTo(64,16);
	printf(" ");
	GoTo(63,16);
	printf(" ");
	GoTo(62,16);
	printf(" ");
//Chu V
	for (int i=11; i<=13; i++){
		GoTo(65,i);
		printf(" ");
	}
	for (int i=11; i<=14; i++){
		GoTo(66,i);
		printf(" ");
	}
	GoTo(67,14);
	printf(" ");
	for (int i=67; i<=70; i++){
		GoTo(i,15);
		printf(" ");
	}
	
	for (int i=11; i<=13; i++){
		GoTo(72,i);
		printf(" ");
	}
	for (int i=11; i<=14; i++){
		GoTo(71,i);
		printf(" ");
	}
	GoTo(70,14);
	printf(" ");
	GoTo(67,11);
	printf(" ");
	GoTo(67,12);
	printf(" ");
	GoTo(67,13);
	printf(" ");
	GoTo(68,14);
	printf(" ");
	GoTo(65,14);
	printf(" ");
	GoTo(66,15);
	printf(" ");
	GoTo(67,16);
	printf(" ");
	GoTo(68,16);
	printf(" ");
	GoTo(69,16);
	printf(" ");
	GoTo(70,16);
	printf(" ");
	GoTo(71,16);
	printf(" ");
	GoTo(71,15);
	printf(" ");
	GoTo(72,15);
	printf(" ");
	GoTo(72,14);
	printf(" ");
	GoTo(73,14);
	printf(" ");
	GoTo(73,13);
	printf(" ");
	GoTo(73,12);
	printf(" ");
	GoTo(73,11);
	printf(" ");
//Chu E2
	for (int i=74; i<=80; i++){
		GoTo(i,11);
		printf(" ");
	}
	for (int i=12; i<=15; i++){
		GoTo(74,i);
		printf(" ");
	}
	for (int i=12; i<=15; i++){
		GoTo(75,i);
		printf(" ");
	}
	for (int i=76; i<=80; i++){
		GoTo(i,15);
		printf(" ");
	}
	for (int i=76; i<=78; i++){
		GoTo(i,13);
		printf(" ");
	}
	GoTo(81,11);
	printf(" ");
	GoTo(81,12);
	printf(" ");
	GoTo(80,12);
	printf(" ");
	GoTo(80,12);
	printf(" ");
	GoTo(79,12);
	printf(" ");
	GoTo(78,12);
	printf(" ");
	GoTo(77,12);
	printf(" ");
	GoTo(76,12);
	printf(" ");
	GoTo(79,13);
	printf(" ");
	GoTo(79,14);
	printf(" ");
	GoTo(78,14);
	printf(" ");
	GoTo(77,14);
	printf(" ");
	GoTo(76,14);
	printf(" ");
	GoTo(81,15);
	printf(" ");
	GoTo(81,16);
	printf(" ");
	GoTo(80,16);
	printf(" ");
	GoTo(79,16);
	printf(" ");
	GoTo(78,16);
	printf(" ");
	GoTo(77,16);
	printf(" ");
	GoTo(76,16);
	printf(" ");
	GoTo(75,16);
	printf(" ");
	GoTo(74,16);
	printf(" ");
//Chu R2
	for (int i=11; i<=15; i++){
		GoTo(82,i);
		printf(" ");
	}
	for (int i=11; i<=15; i++){
		GoTo(83,i);
		printf(" ");
	}
	for (int i=84; i<=87; i++){
		GoTo(i,11);
		printf(" ");
	}
	GoTo(87,12);
	printf(" ");
	GoTo(88,12);
	printf(" ");
	for (int i=84; i<=87; i++){
		GoTo(i,13);
		printf(" ");
	}
	GoTo(87,14);
	printf(" ");
	GoTo(87,15);
	printf(" ");
	GoTo(88,14);
	printf(" ");
	GoTo(88,15);
	printf(" ");
	GoTo(88,11);
	printf(" ");
	GoTo(89,12);
	printf(" ");
	GoTo(89,13);
	printf(" ");
	GoTo(88,13);
	printf(" ");
	GoTo(89,14);
	printf(" ");
	GoTo(89,15);
	printf(" ");
	GoTo(89,16);
	printf(" ");
	GoTo(88,16);
	printf(" ");
	GoTo(87,16);
	printf(" ");
	GoTo(86,12);
	printf(" ");
	GoTo(85,12);
	printf(" ");
	GoTo(86,12);
	printf(" ");
	GoTo(84,14);
	printf(" ");
	GoTo(85,14);
	printf(" ");
	GoTo(86,14);
	printf(" ");
	GoTo(84,15);
	printf(" ");
	GoTo(84,16);
	printf(" ");
	GoTo(83,16);
	printf(" ");
	GoTo(82,16);
	printf(" ");

	GoTo(1,27);
	printf ("%s", "Nhan Enter de tiep tuc");
}

//OUTRO GAME
void Outro(){
    Ket();
    HOutro();
	Sleep(500);
}
void Ket(){
    system("cls");
    int xC=9, yC=21;
    int x1=95,y1=21;
    DoiMau(0,7);
	//Chan
	GoTo(x1, y1);
	printf("%c",19);
	//Đau
	GoTo(x1, y1-1);
	printf("%c",64);
    //
    DoiMau(0,11);
    for(int i=20; i<=21; i++){
        for(int j=24; j<=26; j++){
            GoTo(j,i);
            printf("%c",219);
        }
    }
    for(int i=20; i<=21; i++){
        for(int j=53; j<=55; j++){
            GoTo(j,i);
            printf("%c",219);
        }
    }
    DoiMau(0,9);
    //
    NV(9,21);
    for(int j=10; j<=21; j++){
        Sleep(20);
        XNV(xC,yC);
        Sleep(20);
        NV(j,21);
        xC=j;
    }
    int x=21, y=21;
    for(int k=0; k<3; k++){
        x++; y--;
        Sleep(20);
        XNV(xC,yC);
        Sleep(20);
        NV(x,y);
        xC=x; yC=y;
    }
	x++;
	Sleep(20);
	XNV(xC,yC);
	Sleep(20);
	NV(x,y);
	xC=x; yC=y;
	x++;
	Sleep(20);
	XNV(xC,yC);
	Sleep(20);
	NV(x,y);
	xC=x; yC=y;
    for(int k=0; k<3; k++){
		x++; y++;
		Sleep(20);
		XNV(xC,yC);
		Sleep(20);
		NV(x,y);
		xC=x; yC=y;
    }
    //
    for(int j=30; j<=50; j++){
        Sleep(20);
        XNV(xC,yC);
        Sleep(20);
        NV(j,21);
        xC=j;
    }
    x=50; y=21;
    for(int k=0; k<3; k++){
        x++; y--;
        Sleep(20);
        XNV(xC,yC);
        Sleep(20);
        NV(x,y);
        xC=x; yC=y;
    }
	x++;
	Sleep(20);
	XNV(xC,yC);
	Sleep(20);
	NV(x,y);
	xC=x; yC=y;
	x++;
	Sleep(20);
	XNV(xC,yC);
	Sleep(20);
	NV(x,y);
	xC=x; yC=y;
    for(int k=0; k<3; k++){
		x++; y++;
		Sleep(20);
		XNV(xC,yC);
		Sleep(20);
		NV(x,y);
		xC=x; yC=y;
    }
    //
    for(int j=59; j<=94; j++){
        Sleep(20);
        XNV(xC,yC);
        Sleep(20);
        NV(j,21);
        xC=j;
    }
    Sleep(20);
    XNV(xC,yC);
    Sleep(20);
    NV(86,21);
    //
    xC=x1; yC=y1;
    while(y1>2){
        Sleep(20);
        //Chan 
        GoTo(xC, yC);
        printf(" ");
        //Đau
        GoTo(xC, yC-1);
        printf(" ");
        Sleep(20);
        DoiMau(0,7);
        //Chan
        GoTo(x1, y1);
        printf("%c",19);
        //Đau
        GoTo(x1, y1-1);
        printf("%c",64);
        yC=y1;
        y1--;
    }
    //Chan 
	GoTo(xC, yC);
	printf(" ");
	//Đau
	GoTo(xC, yC-1);
	printf(" ");
}
void HOutro(){
	DoiMau(0,9);
	char x=219; 
	//chu T
	for (int i=30; i<=37; i++){
		GoTo(i,11);
        Sleep(20);
		printf("%c",x);
	}
	for (int i=12; i<=15; i++){
		GoTo(33,i);
        Sleep(20);
		printf("%c",x);
	}
	for (int i=12; i<=15; i++){
		GoTo(34,i);
        Sleep(20);
		printf("%c",x);
	}
	GoTo(30,12); 
	Sleep(20);
    printf("%c",200);
	GoTo(31,12); 
	Sleep(20);
    printf("%c",205);
	GoTo(32,12); 
	Sleep(20);
    printf("%c",205);
	GoTo(38,11);
	Sleep(20);
    printf("%c", 187);
	GoTo(38,12);
	Sleep(20);
    printf("%c", 188);
	GoTo(37,12);
	Sleep(20);
    printf("%c", 205);
	GoTo(36,12);
	Sleep(20);
    printf("%c", 205);
	GoTo(35,12);
	Sleep(20);
    printf("%c", 201);
	GoTo(35,13);
	Sleep(20);
    printf("%c", 186);
	GoTo(35,14);
	Sleep(20);
    printf("%c", 186);
	GoTo(35,15);
	Sleep(20);
    printf("%c", 186);
	GoTo(35,16);
	Sleep(20);
    printf("%c", 188);
	GoTo(34,16);
	Sleep(20);
    printf("%c", 205);
	GoTo(33,16);
	Sleep(20);
    printf("%c", 200);
//Chu H
	for(int i=11; i<=15; i++){
		GoTo(39,i);
		Sleep(20);
        printf("%c",x);
	}
	for(int i=11; i<=15; i++){
		GoTo(40,i);
		Sleep(20);
        printf("%c",x);
	}
	for(int i=41; i<=43; i++){
		GoTo(i,13);
		Sleep(20);
        printf("%c",x);
	}
	for(int i=11; i<=15; i++){
		GoTo(44,i);
		Sleep(20);
        printf("%c",x);
	}
	for(int i=11; i<=15; i++){
		GoTo(45,i);
		Sleep(20);
        printf("%c",x);
	}
	GoTo(41,11);
	Sleep(20);
    printf("%c", 187);
	GoTo(41,12);
	Sleep(20);
    printf("%c", 186);
	GoTo(41,14);
	Sleep(20);
    printf("%c", 201);
	GoTo(42,14);
	Sleep(20);
    printf("%c", 205);
	GoTo(43,14);
	Sleep(20);
    printf("%c", 205);
	GoTo(41,15);
	Sleep(20);
    printf("%c", 186);
	GoTo(41,16);
	Sleep(20);
    printf("%c", 188);
	GoTo(40,16);
	Sleep(20);
    printf("%c", 205);
	GoTo(39,16);
	Sleep(20);
    printf("%c", 200);
	GoTo(46,11);
	Sleep(20);
    printf("%c", 187);
	GoTo(46,12);
	Sleep(20);
    printf("%c", 186);
	GoTo(46,13);
	Sleep(20);
    printf("%c", 186);
	GoTo(46,14);
	Sleep(20);
    printf("%c", 186);
	GoTo(46,15);
	Sleep(20);
    printf("%c", 186);
	GoTo(46,16);
	Sleep(20);
    printf("%c", 188);
	GoTo(45,16);
	Sleep(20);
    printf("%c", 205);
	GoTo(44,16);
	Sleep(20);
    printf("%c", 200);
//Chu E
	for (int i=47; i<=53; i++){
		GoTo(i,11);
		Sleep(20);
        printf("%c",x);
	}
	for (int i=12; i<=14; i++){
		GoTo(47,i);
		Sleep(20);
        printf("%c",x);
	}
	for (int i=12; i<=14; i++){
		GoTo(48,i);
		Sleep(20);
        printf("%c",x);
	}
	for (int i=47; i<=53; i++){
		GoTo(i,15);
		Sleep(20);
        printf("%c",x);
	}
	for (int i=49; i<=51; i++){
		GoTo(i,13);
		Sleep(20);
        printf("%c",x);
	}
	GoTo(54,11);
	Sleep(20);
    printf("%c",187);
	GoTo(54,12);
	Sleep(20);
    printf("%c",188);
	GoTo(53,12);
	Sleep(20);
    printf("%c",205);
	GoTo(52,12);
	Sleep(20);
    printf("%c",205);
	GoTo(51,12);
	Sleep(20);
    printf("%c",205);
	GoTo(50,12);
	Sleep(20);
    printf("%c",205);
	GoTo(49,12);
	Sleep(20);
    printf("%c",201);
	GoTo(52,13);
	Sleep(20);
    printf("%c",187);
	GoTo(52,14);
	Sleep(20);
    printf("%c",188);
	GoTo(51,14);
	Sleep(20);
    printf("%c",205);
	GoTo(50,14);
	Sleep(20);
    printf("%c",205);
	GoTo(49,14);
	Sleep(20);
    printf("%c",201);
	GoTo(54,15);
	Sleep(20);
    printf("%c",187);
	GoTo(54,16);
	Sleep(20);
    printf("%c",188);
	GoTo(53,16);
	Sleep(20);
    printf("%c",205);
	GoTo(52,16);
	Sleep(20);
    printf("%c",205);
	GoTo(51,16);
	Sleep(20);
    printf("%c",205);
	GoTo(50,16);
	Sleep(20);
    printf("%c",205);
	GoTo(49,16);
	Sleep(20);
    printf("%c",205);
	GoTo(48,16);
	Sleep(20);
    printf("%c",205);
	GoTo(47,16);
	Sleep(20);
    printf("%c",200);
//Chu E2
	for (int i=59; i<=65; i++){
		GoTo(i,11);
		Sleep(20);
        printf("%c",x);
	}
	for (int i=12; i<=14; i++){
		GoTo(59,i);
		Sleep(20);
        printf("%c",x);
	}
	for (int i=12; i<=14; i++){
		GoTo(60,i);
		Sleep(20);
        printf("%c",x);
	}
	for (int i=59; i<=65; i++){
		GoTo(i,15);
		Sleep(20);
        printf("%c",x);
	}
	for (int i=61; i<=63; i++){
		GoTo(i,13);
		Sleep(20);
        printf("%c",x);
	}
	GoTo(66,11);
	Sleep(20);
    printf("%c",187);
	GoTo(66,12);
	Sleep(20);
    printf("%c",188);
	GoTo(65,12);
	Sleep(20);
    printf("%c",205);
	GoTo(64,12);
	Sleep(20);
    printf("%c",205);
	GoTo(63,12);
	Sleep(20);
    printf("%c",205);
	GoTo(62,12);
	Sleep(20);
    printf("%c",205);
	GoTo(61,12);
	Sleep(20);
    printf("%c",201);
	GoTo(64,13);
	Sleep(20);
    printf("%c",187);
	GoTo(64,14);
	Sleep(20);
    printf("%c",188);
	GoTo(63,14);
	Sleep(20);
    printf("%c",205);
	GoTo(62,14);
	Sleep(20);
    printf("%c",205);
	GoTo(61,14);
	Sleep(20);
    printf("%c",201);
	GoTo(66,15);
	Sleep(20);
    printf("%c",187);
	GoTo(66,16);
	Sleep(20);
    printf("%c",188);
	GoTo(65,16);
	Sleep(20);
    printf("%c",205);
	GoTo(64,16);
	Sleep(20);
    printf("%c",205);
	GoTo(63,16);
	Sleep(20);
    printf("%c",205);
	GoTo(62,16);
	Sleep(20);
    printf("%c",205);
	GoTo(61,16);
	Sleep(20);
    printf("%c",205);
	GoTo(60,16);
	Sleep(20);
    printf("%c",205);
	GoTo(59,16);
	Sleep(20);
    printf("%c",200);
//Chu N
	for (int i=11; i<=15; i++){
		GoTo(67,i);
		Sleep(20);
        printf("%c",x);
	}
	for (int i=11; i<=15; i++){
		GoTo(68,i);
		Sleep(20);
        printf("%c",x);
	}
	for(int i=11, j=69; i<=14; i++){
		GoTo(j,i);
		Sleep(20);
        printf("%c",x);
		GoTo(j,i+1);
		Sleep(20);
        printf("%c",x);
		j++;
	}
	for (int i=11; i<=15; i++){
		GoTo(73,i);
		Sleep(20);
        printf("%c",x);
	}
	for (int i=11; i<=15; i++){
		GoTo(74,i);
		Sleep(20);
        printf("%c",x);
	}
	GoTo(67,16);
	Sleep(20);
    printf("%c",200);
	GoTo(68,16);
	Sleep(20);
    printf("%c",205);
	GoTo(69,16);
	Sleep(20);
    printf("%c",188);
	GoTo(72,16);
	Sleep(20);
    printf("%c",200);
	GoTo(73,16);
	Sleep(20);
    printf("%c",205);
	GoTo(74,16);
	Sleep(20);
    printf("%c",205);
	GoTo(75,16);
	Sleep(20);
    printf("%c",188);
	GoTo(69,13);
	Sleep(20);
    printf("%c",201);
	GoTo(69,14);
	Sleep(20);
    printf("%c", 186);
	GoTo(69,15);
	Sleep(20);
    printf("%c", 186);
	GoTo(70,11);
	Sleep(20);
    printf("%c",187);
	GoTo(71,12);
	Sleep(20);
    printf("%c",187);
	GoTo(72,13);
	Sleep(20);
    printf("%c",187);
	GoTo(70,14);
	Sleep(20);
    printf("%c",200);
	GoTo(71,15);
	Sleep(20);
    printf("%c",200);
	GoTo(75,11);
	Sleep(20);
    printf("%c", 187);
	GoTo(75,12);
	Sleep(20);
    printf("%c", 186);
	GoTo(75,13);
	Sleep(20);
    printf("%c", 186);
	GoTo(75,14);
	Sleep(20);
    printf("%c", 186);
	GoTo(75,15);
	Sleep(20);
    printf("%c", 186);
//Chu D
	for (int i=11; i<=15; i++){
		GoTo(76,i);
		Sleep(20);
        printf("%c",x);
	}
	for (int i=11; i<=15; i++){
		GoTo(77,i);
		Sleep(20);
        printf("%c",x);
	}
	for (int i=12; i<=14; i++){
		GoTo(81,i);
		Sleep(20);
        printf("%c",x);
	}
	for (int i=12; i<=14; i++){
		GoTo(82,i);
		Sleep(20);
        printf("%c",x);
	}
	for (int i=78; i<=81; i++){
		GoTo(i,11);
		Sleep(20);
        printf("%c",x);
	}
	for (int i=78; i<=81; i++){
		GoTo(i,15);
		Sleep(20);
        printf("%c",x);
	}
	GoTo(76,16);
	Sleep(20);
    printf("%c",200);
	GoTo(77,16);
	Sleep(20);
    printf("%c",205);
	GoTo(78,16);
	Sleep(20);
    printf("%c",205);
	GoTo(79,16);
	Sleep(20);
    printf("%c",205);
	GoTo(80,16);
	Sleep(20);
    printf("%c",205);
	GoTo(81,16);
	Sleep(20);
    printf("%c",205);
	GoTo(82,16);
	Sleep(20);
    printf("%c",188);
	GoTo(78,12);
	Sleep(20);
    printf("%c",201);
	GoTo(78,13);
	Sleep(20);
    printf("%c", 186);
	GoTo(78,14);
	Sleep(20);
    printf("%c", 186);
	GoTo(79,12);
	Sleep(20);
    printf("%c",205);
	GoTo(80,12);
	Sleep(20);
    printf("%c",205);
	GoTo(82,11);
	Sleep(20);
    printf("%c", 187);
	GoTo(83,12);
	Sleep(20);
    printf("%c", 187);
	GoTo(83,13);
	Sleep(20);
    printf("%c", 186);
	GoTo(83,14);
	Sleep(20);
    printf("%c", 186);
	GoTo(82,15);
	Sleep(20);
    printf("%c",201);
	GoTo(883,15);
	Sleep(20);
    printf("%c",188);
}


//Noi chay chuong trinh (MAIN)
int main(){
	ShowCur(false);	//An con tro
    Intro();
	DoiMau(0,11);
	DKy_DNhap();
    system("cls");
    return 0;
}
