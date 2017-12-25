/*
	AD-SOYAD		=ÖZGÜR KAN
	ÖĞRENCİ NUMARASI 	=15011702
	DERS			=PROGRAMLAMA DİLLERİ
	GRUP NO			=3	

								    MAİN FONKSİYONU AÇIKLAMA
İlk önce argv kullanarak kullanıcıdan arama yapmak istediği dizin bilgisini aldım.Daha sonra main fonksiyonu içerisinde pthread için gerekli olan işlemleri yaptım.
argv den gelen bilgilerin doğruluğunu kontrol ettim ve eğer girilen yol doğruysa dosyayı açtım.Dosyayı açtıktan sonra kullanıcıdan aramak istediği kelime ve arama numarasını aldım.
Ana fonksiyonda pthread başlatıp arama fonksiyonunu çalıştırdım ve ana fonksiyonun pthreadinin beklemesini sağladım.Arama fonksiyonundan dönüldüğünde ise açtığım dosyayı kapattım.
								
								    ARAMA FONKSİYONU AÇIKLAMA	
Arama fonksiyonunda temel olarak sonuçları yazmak için kullanıcıdan aldığım arama numarasyıla bir txt belgesi oluşturdum.Daha sonra dosya içerisindeki bütün belgeleri döngüyle dolaşıp uzantılarının
.txt olup olmadığını kontrol ettim.Eğer uzantısı .txt ise o belgeyi açtım.Belge içerisindeki tüm satırları döngüyle gezip aradığımız kelime olup olmadığını kontrol ettim.
Eğer aradığımız kelime varsa bunları açmış olduğum sonuç belgesine yazdırdım.Bütün txt belgeleri okunup bittikten sonra sonuçların hangi belgede gösterileceğini ve kaç tane .txt uzantılı belge
okuduğumuzu ekrana yazdırdım.

NOT=Sonuçların girileceği dosyanın ismini arama numarası değişkeniyle kullanıcıdan aldım.Böyle yapmamın sebebi kullanıcının gerçek dosyalarındaki verilerini kaybetmemek istemem.
Örneğin kullanıcının girdiği dosya yolunda kullanıcı için önemli olan 1.txt belgesi olduğunu düşünelim.Arama numarası 1 den başlayıp otomatik artsaydı biz bu 1.txt belgesini sonuçları yazmak için 
açtığımızda içindeki veriler silinecekti yada içerisindeki bilgiler duracak ve biz üstüne yazacaktık ve karışıklığa neden olacakı.

								    PROGRAMI ÇALIŞTIRMA ŞEKLİ:
./hellomake [aramak istediğiniz dosya yolunu giriniz.]
Aramak istediğiniz kelimeyi giriniz.
Arama numarasını giriniz.

								   ÖRNEK BİR PROGRAM ÇALIŞTIRMASI:
ozgur@ozgur-VirtualBox:~/Masaüstü/sınav$ ./hellomake /home/ozgur/Masaüstü/sınav
Lütfen aranacak kelimeyi büyük küçük harfe dikkat ederek giriniz:ozgur
Arama numarası giriniz:5
thread arama fonksiyonunu çalıştırdı.
Dosya içerisinde 3 tane txt uzantılı belge bulundu.
Girdiğiniz kelime bu txt belgelerinde arandı.
Sonuçlar 5.txt belgesinde gözükecektir.



*/


#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>

void* arama(void *kelime);
int arama_numarasi;
char kelime[100];
int i=0;
FILE *fp;
char temp[512];
int find_result = 0;
FILE *outfile;
DIR *directory;
struct dirent* file; 

int main (int argc, char *argv[]) {


pthread_t tid;						//threadin id'si tanımladım.
pthread_attr_t attr;					//thread'in attribute'lerini tanımladım.
pthread_attr_init(&attr);				//thread initialized ettim.	
   
      /* parametre sayısı 2 den farklı ise hata versin */
	if (argc != 2) {
	        printf("Hata lütfen parametreleri dogru giriniz.\n");	
	        exit(1);
    	}
    
	directory = opendir(argv[1]);			//argv[1]den gelen dosya yoluyla dosya açılır.
	
	/*Eğer dosya açılamazsa hata versin*/
    	if (directory == NULL) {
        	printf("Hata girdiğiniz adres yanlış veya eksiktir.\n");
        	exit(2);
    	}

	/*Aranacak kelimeyi kullanıcıdan aldım*/
	printf("Lütfen aranacak kelimeyi büyük küçük harfe dikkat ederek giriniz:");
	scanf("%s",kelime);
	
	/*Kullanıcıdan arama numarası aldım.*/
	printf("Arama numarası giriniz:");
	scanf("%d",&arama_numarasi);

	pthread_create(&tid,&attr,arama,kelime);	//thread yarattım ve arama fonksiyonuna yönlendirdim.
	pthread_join(tid,NULL);				//Programın ana threadinin beklemesini sağladım.
	
	closedir(directory);				//Açtığımız dosyayı kapattım.
return 0;
    }

//////////////////////// 	ARAMA FONKSİYONU	//////////////////////////////////////

void* arama(void *kelime) 
{

	printf("thread arama fonksiyonunu çalıştırdı.\n");			//Fonksiyonun çalıştığını ekrana yazdırdım.
	
	/*--burada iki tane karakter türünde dizi oluşturup girilen arama numarasını birinci diziye
	    .txt uzantısını ise ikinci diziye verip bu ikisini birbirlerine bağladım.Sonuç olarak 
	   elimizde kullanıcının girdiği sayı.txt dosyası oluştu.Bu dosyayı sonuçları yazdırmak için kullandım.
	*/
	char kontrol[20];
	char kontrol1[4];
	strcpy(kontrol1, ".txt");
	sprintf(kontrol,"%d",arama_numarasi);
	strcat(kontrol,kontrol1);
	/*--*/
		
	outfile=fopen(kontrol,"w");						//Sonuçların yazılacağı txt dosyasını açtım.
	fprintf(outfile,"ARANAN KELİME:%s \n\n",(char*)kelime);			//Sonuç dosyasının ilk satırına aranan kelimeyi yazdım.

   while ((file=readdir(directory)) != NULL) {					//dosyada bulunan bütün belgeleri okumak için while döngüsü oluşturdum.
	int lenght=strlen(file->d_name);					//okuduğu belgenin isminin uzunluğunu aldım.
	if(strncmp(file->d_name+lenght - 4,".txt",4)==0){			//Burada dosyanın uzantısının txt olup olmamasını kontrol ettim.
		fp = fopen(file->d_name, "r");					//Dosyanın uzantısı txt ise dosyayı okuma konumunda açtım.
		find_result=0;							//satır bilgisini tutacak olan değişken
		if (fp == NULL) {						//Eğer fp null'sa dosya açılamamıştır hata ver.Değilse dosya açılmıştır devam et.
		printf("dosya açılamadı");
		}
		else{			
			while(fgets(temp, 512, fp) != NULL) {			//Burada belge içerisindeki tüm satırlar bitene kadar okumak için döngü kullandım.
				find_result++;					//Okuduğumuz her satırda satır sayımızı arttırdım.
					if((strstr(temp, kelime)) != NULL) {	//Okuduğumuz satırda aradığımız kelimenin geçip geçmediğini kontol ettim.				
					fprintf(outfile,"%s dosyasında %d.satırda bulundu.\n",file->d_name,find_result);//Eğer kelime satırda bulunduysa bunu sonuç dosyamıza yazdım.	
					}		
			}				
			fclose(fp);						//Okuduğumuz belgeyi kapattım.			
		}
		i++;								//Kaç tane txt okuduğumuzu bulmak için i'yi bir arttırdım.
	}	
    }
	printf("Dosya içerisinde %d tane txt uzantılı belge bulundu.\nGirdiğiniz kelime bu txt belgelerinde arandı.\n",i-1);//Ekrana kaç tane txt belgesinde arama yaptığımızı yazdım.
	printf("Sonuçlar %d.txt belgesinde gözükecektir.\n",arama_numarasi);	//Ekrana sonuçların nerede gözükeceği bilgisi verildi.
	fclose(outfile);							//sonuçları yazdırdığımız dosyamızı kapattım.
}


