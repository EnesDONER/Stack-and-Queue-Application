// VeriYapilariDonemProjesi2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
struct Dugum {
	int veri; //düðümün sayýsal deðeri
	Dugum* sonraki;//sonraki düðüme iþaretçi
}; 
struct Kuyruk{ Dugum* bas; //kuyruðunbaþýndaki elemanýnadresini tutar
Dugum* son;//kuyruðun sonundaki elemanýn adresini tutar
void olustur(); //baþlangýç için gereken tanýmlarý içerir
void kapat(); //program bitimindebellek iadesi yapar
void ekle(int); //kuyruða yeni veri ekler
int cikar();//kuyruktan sýradaki elemaný çýkarýr
bool bosMu();//kuyruk boþ mu kontrol eder
}; 
struct Yigin {
	Kuyruk k1, k2; //yýðýn için kullanýlacak kuyruk deðiþkenleri
	void olustur(); //baþlangýç için gereken tanýmlarý içerir
	void kapat(); //program bitimindebellek iadesi yapar
	void ekle(int); //kuyruða yeni veri ekler
	int cikar(); //kuyruktan sýradaki elemaný çýkarýr
	bool bosMu(); //kuyruk boþ mu kontrol eder
	int tepe();      //yýðýnýn tepesindeki elemaný okur
	void yazdir();  //yýðýn elemanlarýný sýrayla ekrana yazar
}; 
void siraliEkle(Yigin* s, int x);
void yiginCikar(Yigin* s);

int main()
{
	Yigin y;
	y.olustur();
	y.ekle(3);
	y.ekle(1);
	y.ekle(7);
	y.ekle(4);
	y.ekle(8);
	std::cout << "Orijinal Yigin:" << std::endl;
	y.yazdir();
	std::cout << "\n";
	yiginCikar(&y);
	std::cout << "---yiginCikar fonsiyon cagirisi---"<<"\n";
	y.yazdir();
	std::cout << "\n";
	siraliEkle(&y,5);
	std::cout << "---siraliEkle 5 fonsiyon cagirisi---" << "\n";
	y.yazdir();

}
void Kuyruk::olustur() {
	bas = NULL;
	son = NULL;
}
void Kuyruk::kapat() {
	Dugum* p;
	while (bas)
	{
		p = bas;
		bas = bas->sonraki;
		delete p;
	}
}
void Kuyruk::ekle(int yeni) {
	Dugum* yenidugum = new Dugum;
	yenidugum->veri = yeni;
	yenidugum->sonraki = NULL;
	if (bas==NULL)
	{
		bas = yenidugum;
		son = bas;
	}
	else {
		son->sonraki = yenidugum;
		son = yenidugum;
	}

}
int Kuyruk::cikar() {
	Dugum* ustdugum;
	int gecici;
	ustdugum = bas;
	bas = bas->sonraki;
	gecici = ustdugum->veri;
	delete ustdugum;
	return gecici;
}
bool Kuyruk::bosMu() {
	return bas == NULL;
}
void Yigin::olustur() {
	k1.bas = NULL;
	k2.bas = NULL;
	k1.son = NULL;
	k2.son = NULL;

}
void Yigin::ekle(int yeni) {
	k2.ekle(yeni);
	while (!k1.bosMu())
	{
		k2.ekle(k1.bas->veri);
		k1.cikar();
	}
	Kuyruk tut= k1;
	k1 = k2;
	k2 = tut;
}
int Yigin::cikar() {
	if (k1.bosMu())
	{
		return 0;
	}
	k1.cikar();
}
int Yigin::tepe() {
	if (k1.bosMu())
		return -1;
	return k1.bas->veri;
}
void Yigin::yazdir() {
	while (!k1.bosMu())
	{
		std::cout << k1.bas->veri<<"  ";
		k2.ekle(k1.bas->veri);
		k1.bas = k1.bas->sonraki;
	}
	Kuyruk tut = k1;
	k1 = k2;
	k2 = tut;	
}
bool Yigin::bosMu() {
	return k1.bosMu();
} 
void Yigin::kapat() {
	Kuyruk k;
	while (k1.bas)
	{
		k = k1;
		k1.bas = k1.bas->sonraki;
		delete k.bas;
	}
}
void siraliEkle(Yigin* s, int x) {
	if (s->bosMu() or x>s->tepe())
	{
		s->ekle(x);
		return;
	}
	int temp = s->cikar();
	siraliEkle(s, x);
	s->ekle(temp);
}
void yiginCikar(Yigin* s) {
	if (!s->bosMu())
	{
		int x = s->cikar();
		yiginCikar(s);
		siraliEkle(s, x);
	}
}
