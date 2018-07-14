# programla dilleri 2017 güz dönemi Cihan Tayşi Hocamızın 2.vize için bizden istediği uygulama

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
