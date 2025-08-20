[[25.07.23]]
## Näytön Sommittelua
### Printit joiden täytyy näkyä:
Vaatimuksista:
1. Näyttää neulatunnit ruudulta
2. Näyttää ruudulta, mikä neuloista on valittu
Koska näyttö ei päivity kuin maks kerran tunnissa:
3. tarvitaan näytöltä aikatietoja
	1. tieto kuinka kauan sitten viimeisin resetti on
	2. tieto kuinka kauan sitten viimeisin aktiivisuusaika oli.
	3. Kumpaakaan ei saada ilman A. erillistä RTC moduulia tai B. deep sleep moden hylkäämistä.

### 2.
Saadaan alareunasta Adafruit_GFX::drawChar metodilla, koska sillä voi piirtää yhden ascii merkin, määrittää sen värin, sekä taustan värin. Valitsemalla yhden neulan, neulaa vastaava merkki vaihtaa väriäään