[[25.07.15]]

## varmistetaan jokaisen komponentin toimivuus itsenäisesti toisistaan

### Kielirele
1. Kiinnitetään kielireleen toinen pää maahan ja toinen GPIO-input-piniin ja vaihdellaan led-builtinin tilaa. Printataan myös serial outputtiin 
- Ainakin yleismittarin kanssa keilirele toimii. Noin 1-2 cm päässä magneetista aktivoituu kiinni-tilaan.

[[25.07.18]]

![something](./attachments/IMG20250718194050.jpg?raw=true "Title")

1. tein testauskoodinpätkän blink_test, jolla saa kytkimien toimivuutta testattua helposti. (Jos sininen led palaa, kielirele on aktivoitu)
2. Juotin kielireleen piuhoihin kiinni
3. Testasin magneettien kanssa
Testasin myös miten magneettikenttä pääsee puun läpi bambuleikkuulaudalla:
![](./attachments/IMG20250718194119.jpg||500)
Laudan alla on siis neodyymimagneetti: ja toimiihan se!

## etäisyysanturi
[[25.07.18]]
 ![](./attachments/IMG20250718191820.jpg||500?raw=true "Title")
1. Juotin pinnit kiinni
2. Kirjoitin testauskoodin ir_sensor_test
3. Kytkin kiinni ja se toimii!

> [!NOTE]
> Outputtia ei ole säädetty ollenkaan nyt. Analog output näyttää joko 4096 tai 0, mutta kuitenkin järkevästi. 4096 kun asia on kaukana, 0 kun se on lähellä.

4. tein sähkärin teipistä sensorille putken, jotta vastaanottaja havaitsisi lähettäjän valon vain yhdestä suunnasta. Tämä oli huomioitu dokumentaatiossakin, oivasti. 
5. Teippihattu sai anturin toimimaan melko täydellisesti!
Alla olevissa kuvissa: Punaisen valon palaessa: output: 0, muuten output: 4096. Äänivarsi on ensimmäisessä kuvassa lepotilassa ja toisessa aktiivi-tilassa. Anturri toimii siis täysin oikein.
![img](./attachments/IMG20250718205333.jpg||500)
![](./attachments/IMG20250718205340.jpg?raw=true)

> [!NOTE] 
> Anturin jatkosäätö
> Näillä näkymin en näe tarpeelliseksi tutkia anturin toiminnallisuutta sen enempää. Sehän toimii tarkoitetulla tavalla!

## Epaper
[[25.07.20]]
testaan käyttäen tätä videota: https://www.youtube.com/watch?v=El38zVmog14&ab_channel=CodingWithBrett

#### Muutoksia
Koska piikkirimojen kanssa meni vähän häsäykseksi eikä mulla oo muutamassa io portissa piikkejä ollenkaan, täytyy RST pin vaihtaa toiseksi näytön käyttämiseksi.
Vahdoin rivilllä 223 (GxEPD2_display_selection_new_style.h, gxepd2 kirjaston hello world esimerkin headereissa.): `GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> display(GxEPD2_DRIVER_CLASS(/*CS=5*/ EPD_CS, /*DC=*/ 17, /*RST=*/ 27, /*BUSY=*/ 4)); // my suggested wiring and proto board` RSTn 16 -> 27

Eli vaihdoin siis oikean ajuriluokan porttimääritelmää.

Lukuisien ajuriluokkien joukosta ChatGPT suositteli valitsemaan GxEPD2_260. Samankokoisille näytöille oli useita luokkia, joiden eroista en ihan saanut selvää. Valintaa ei helpota, ettei Waveshare merkitse näytön spekseissä tätä luokkaa tai oikeastaan mitään muutakaan vastaavia speksejä dokumentaatiossa.

Ekaks ei toiminut. Luokka olikin väärä! Kävin läpi useamman luokan ja oikea olikin: 
` #define GxEPD2_DRIVER_CLASS GxEPD2_266_BN // DEPG0266BN 152x296, SSD1680, (FPC7510), TTGO T5 V2.66, TTGO T5 V2.4.1

Olo huojentunut! debuggasin tarkastamalla portit visuaalisesti, että johdot olivat oikeissa paikoissa ja näytön puolelta yleismittarilla, että kaikki pinnit olivat aktiivisia. Onneksi ratkaisu oli suht yksinkertainen.
![img](./attachments/IMG20250720140437.jpg)



