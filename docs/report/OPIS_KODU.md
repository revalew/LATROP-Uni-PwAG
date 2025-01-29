### `main`
Plik ten to plik nagłówkowy definiujący stałe, zmienne globalne, oraz deklaracje funkcji używanych w aplikacji. Oto szczegóły:

#### Stałe
- `DEFAULT_WIDTH`, `DEFAULT_HEIGHT`: Domyślna szerokość i wysokość okna gry.
- `FRAMETIME`: Czas między aktualizacjami (odpowiednik FPS = 1/FRAMETIME).
- `CONST_DT`: Stały odstęp czasu w sekundach używany do aktualizacji logiki gry.
- `RADDEG`: Stała konwersji z radianów na stopnie.

#### Globalne zmienne
- `width`, `height`: Wymiary ekranu.
- `mousex`, `mousey`: Aktualna pozycja myszy.
- `keystates`: Tablica śledząca stan klawiszy na klawiaturze.
- `paused`: Informacja o tym, czy gra jest wstrzymana.
- `nmap_enabled`: Flaga określająca, czy normal mapping jest włączony.
- `fade`: Wartość używana do efektu przyciemnienia ekranu.
- `Player player`: Obiekt gracza.
- `Map map`: Obiekt mapy.
- `current_level`: Aktualny poziom gry.

#### Funkcje główne
1. **`update(int value)`**  
   - Aktualizuje logikę gry.
   - Rejestruje ruch myszki, aktualizuje gracza oraz mapę.
   - Obsługuje ekran wygaszania, jeśli gracz zginie lub ukończy poziom.
   - Wywoływana cyklicznie za pomocą `glutTimerFunc`.

2. **`respawn()`**  
   - Odpowiada za odrodzenie gracza po śmierci.
   - Resetuje ekran wygaszania i ustawia gracza na pozycji startowej.

3. **`nextLevel()`**  
   - Wczytuje kolejny poziom gry.
   - Ładuje mapę i wywołuje `respawn`.

4. **`draw()`**  
   - Renderuje całą scenę gry, w tym portale, mapę i gracza.
   - Obsługuje tryb `wireframe` dla wizualizacji.

5. **`drawPortals()`**  
   - Renderuje portale, w tym ich wnętrza, obrysy i widoki z innych perspektyw.

6. **`drawOverlay()`**  
   - Renderuje elementy 2D, takie jak celownik, komunikaty "Pauza" i efekty wygaszania ekranu.

7. **`mouse_moved(int x, int y)`**  
   - Aktualizuje pozycję kursora myszy.

8. **`mouse_pressed(int button, int state, int x, int y)`**  
   - Wywołuje odpowiednią reakcję na naciśnięcie przycisku myszy.

9. **`key_down(unsigned char key, int x, int y)`**  
   - Rejestruje wciśnięcie klawisza.
   - Obsługuje specjalne akcje, takie jak pauza, odrodzenie, przejście do następnego poziomu czy włączenie trybu `wireframe`.

10. **`key_up(unsigned char key, int x, int y)`**  
    - Aktualizuje stan zwolnienia klawisza w tablicy `keystates`.

11. **`resize(int w, int h)`**  
    - Obsługuje zmianę rozmiaru okna i aktualizuje macierze projekcji OpenGL.

12. **`window_status(int state)`**  
    - Pauzuje grę, gdy okno traci widoczność.

13. **`setup(int *argc, char **argv)`**  
    - Inicjalizuje kontekst OpenGL, wczytuje tekstury, ustawia oświetlenie i przypisuje funkcje callback do zdarzeń.

#### `main(int argc, char **argv)`
- Wywołuje funkcję `setup` i uruchamia główną pętlę gry `glutMainLoop`.



</br>
</br>

---

</br>
</br>


### `map`

#### Atrybuty
- **`std::vector<Box> walls`**: Lista ścian mapy.
- **`std::vector<Box> acid`**: Lista basenów kwasu.
- **`GLfloat lightpos[4]`**: Pozycja światła punktowego.
- **`float startpos[3]`**: Pozycja startowa gracza.
- **`float cakepos[3]`**: Pozycja "ciastka".
- **`Box cakeBox`**: Obiekt kolizji "ciastka".

#### Metody główne
1. **`void load(const char *filename)`**
   - Wczytuje mapę z pliku tekstowego:
     - Linie zaczynające się od `w` definiują ściany.
     - Linie zaczynające się od `t` definiują podłogi/płytki.
     - `a` definiuje baseny kwasu.
     - `l` określa pozycję światła.
     - `s` definiuje pozycję startową gracza.
     - `c` definiuje pozycję "ciastka".
   - Wartości są przetwarzane i dodawane do odpowiednich list (`walls`, `acid`).

2. **`void draw(bool nmap)`**
   - Rysuje mapę w zależności od trybu:
     - `wireframe_mode` włącza rendering siatki (bez tekstur).
     - W przeciwnym razie stosowany jest normal mapping lub oświetlenie standardowe.
   - Rysowane są ściany, baseny kwasu, "ciastko" i lampa.

3. **`void drawFromPortal(const Portal& portal, bool nmap)`**
   - Rysuje widoczne elementy mapy z perspektywy portalu:
     - Uwzględnia ograniczenia widoczności na podstawie kierunku portalu.

4. **`void drawBox(Box &b)`**
   - Rysuje sześcian na podstawie współrzędnych prostokąta `Box`.

5. **`void drawCake()`**
   - Rysuje model "ciastka" w jego pozycji.

6. **`void drawLamp()`**
   - Rysuje lampę w pozycji światła.

#### Kolizje
1. **`bool collidesWithWall(Box &bbox)`**
   - Sprawdza kolizje z dowolną ścianą mapy.

2. **`bool collidesWithAcid(Box &bbox)`**
   - Sprawdza kolizje z basenami kwasu.

3. **`bool collidesWithCake(Box &bbox)`**
   - Sprawdza kolizje z "ciastkiem".

4. **`bool pointInWall(float x, float y, float z, Box *box)`**
   - Sprawdza, czy punkt `(x, y, z)` znajduje się wewnątrz ściany.




</br>
</br>

---

</br>
</br>




### `box`

#### Klasa `Box`

##### Atrybuty:
1. **`float x1, y1, z1`**:
   - Dolny lewy przedni róg prostokąta (współrzędne minimalne).

2. **`float x2, y2, z2`**:
   - Górny prawy tylny róg prostokąta (współrzędne maksymalne).

3. **`TEXTURE_ID type`**:
   - Typ tekstury/materiału przypisany do obiektu (`TID_NONE` jako domyślny).

##### Konstruktory:
1. **`Box()`**:
   - Inicjalizuje prostokąt z wartościami domyślnymi (wszystkie współrzędne na `0` i brak tekstury).

2. **`Box(float x1, float y1, float z1, float x2, float y2, float z2, TEXTURE_ID type = TID_NONE)`**:
   - Tworzy prostokąt na podstawie współrzędnych i opcjonalnego typu tekstury.
   - Współrzędne są automatycznie sortowane tak, aby `x1 <= x2`, `y1 <= y2`, `z1 <= z2`.

3. **`Box(float *val, TEXTURE_ID type = TID_NONE)`**:
   - Tworzy prostokąt na podstawie tablicy sześciu wartości `val` i opcjonalnego typu tekstury.

##### Metody:
1. **`void set(float x1, float y1, float z1, float x2, float y2, float z2, TEXTURE_ID type = TID_NONE)`**:
   - Ustawia współrzędne prostokąta, sortując je automatycznie w kolejności rosnącej.

2. **`bool collide(const Box &b)`**:
   - Sprawdza, czy ten prostokąt koliduje z innym prostokątem.
   - Zwraca `true`, jeśli prostokąty nachodzą na siebie, lub `false` w przeciwnym razie.

3. **`bool collide(float x, float y, float z)`**:
   - Sprawdza, czy punkt o współrzędnych `(x, y, z)` znajduje się wewnątrz prostokąta.
   - Zwraca `true` dla punktu wewnętrznego i `false` w przeciwnym razie.




</br>
</br>

---

</br>
</br>




### `player`

#### Atrybuty klasy `Player`
1. **Pozycja i rotacja:**
   - `float x, y, z`: Pozycja gracza.
   - `float xrot, yrot`: Rotacja widoku w osiach X i Y.
   - `float xspeed, yspeed, zspeed`: Prędkość ruchu w osiach X, Y i Z.

2. **Stan gracza:**
   - `PLAYER_STATE state`: Aktualny stan gracza (np. żywy, umierający, zwycięzca).
   - `bool onGround`: Informacja, czy gracz stoi na ziemi.

3. **Portale i strzały:**
   - `Portal portals[2]`: Tablica dwóch portali (niebieskiego i pomarańczowego).
   - `Shot shots[2]`: Tablica dwóch strzałów (dla portali).


#### Implementacje kluczowych metod
1. **`void create(float x, float y, float z)`**
   - Ustawia początkową pozycję gracza i resetuje jego stan, prędkości oraz portale.

2. **`void update(float dt, bool *keystates, float mousedx, float mousedy, Map &map)`**
   - Aktualizuje pozycję i rotację gracza na podstawie wejść od myszy i klawiatury.
   - Obsługuje kolizje z mapą (ściany, kwas, "ciastko") i portale.
   - Obsługuje grawitację, skoki oraz ruch w kierunkach W/S/A/D.
   - Przesuwa gracza przez portale, jeśli wejdzie w ich obszar.

3. **`void mousePressed(int button)`**
   - Reaguje na kliknięcia myszy:
     - Lewy przycisk: strzela niebieskim portalem.
     - Prawy przycisk: strzela pomarańczowym portalem.
     - Środkowy przycisk: dezaktywuje oba portale.

4. **`void setView()`**
   - Ustawia widok kamery zgodnie z pozycją i rotacją gracza w przestrzeni.

5. **`bool portalsActive()`**
   - Sprawdza, czy oba portale są aktywne.

6. **`void drawPortalStencils()`**
   - Renderuje maski portali.

7. **`void drawPortalOutlines()`**
   - Rysuje kolorowe obrysy portali (niebieski i pomarańczowy).

8. **`void drawShots()`**
   - Rysuje aktywne strzały portali, jeśli takie istnieją.

#### Mechanika portali
- Gracz może strzelać portalami, a ich kolizje z mapą są obsługiwane w funkcji `update`.
- Jeśli gracz przechodzi przez portal, jest automatycznie przenoszony do miejsca drugiego portalu, z uwzględnieniem rotacji i przemieszczenia.

#### Stan gracza
- Gracz może znajdować się w jednym z trzech stanów:
  - `PS_ALIVE`: Gra toczy się normalnie.
  - `PS_DYING`: Gracz umiera (np. po wejściu w kwas).
  - `PS_WON`: Gracz osiąga cel gry (np. zdobywa "ciastko").




</br>
</br>

---

</br>
</br>



### `portal`

#### Atrybuty klasy `Portal`
1. **`float x, y, z`**:
   - Pozycja portalu w przestrzeni trójwymiarowej.

2. **`PORTAL_DIR dir`**:
   - Kierunek, w którym portal jest skierowany (np. `PD_RIGHT`, `PD_FRONT`, `PD_LEFT`, `PD_BACK`, `PD_NONE`).

3. **`bool active`**:
   - Informacja, czy portal jest aktywny.


#### Implementacje kluczowych metod
1. **`void place(float x, float y, float z, PORTAL_DIR dir, Map& map)`**
   - Ustawia portal w pozycji `(x, y, z)` w określonym kierunku `dir`.
   - Pozycja jest zaokrąglana, aby portal lepiej dopasował się do powierzchni.
   - Sprawdza, czy przed portalem nie ma przeszkód (kolizje z mapą).

2. **`void placeOnBox(Box &box, float hitx, float hity, float hitz, Map& map)`**
   - Umieszcza portal na powierzchni obiektu `Box`, biorąc pod uwagę miejsce trafienia (np. strzał portalu).
   - Wybiera najbliższą ścianę (lewa, prawa, przód, tył) i umieszcza portal w odpowiednim kierunku.

3. **`bool inPortal(Box &box)`**
   - Sprawdza, czy obiekt `Box` znajduje się w obszarze portalu, uwzględniając kierunek.

4. **`bool throughPortal(float r, float s, float t)`**
   - Sprawdza, czy punkt `(r, s, t)` przeszedł przez portal, na podstawie jego kierunku i pozycji.

5. **`void disable()`**
   - Dezaktywuje portal.

6. **`float getFromRotation()` i `float getToRotation()`**
   - Zwracają kąty rotacji portalu względem osi Z:
     - `getFromRotation()` - rotacja w kierunku widoku portalu.
     - `getToRotation()` - rotacja z widoku portalu do osi Z.

7. **`void drawStencil()`**
   - Rysuje maskę portalu, co jest wykorzystywane w efektach z użyciem bufora stencil.

8. **`void drawOutline(PORTAL_COLOR color)`**
   - Rysuje obrys portalu w zależności od jego koloru (niebieski lub pomarańczowy).


### Mechanika portali
1. **Tworzenie portali:**
   - Portale są umieszczane na powierzchniach obiektów, o ile spełnione są odpowiednie warunki (np. brak przeszkód w obszarze portalu).
   - Pozycja portalu jest automatycznie zaokrąglana dla lepszego dopasowania.

2. **Interakcja z obiektami:**
   - Portal może sprawdzić, czy obiekt znajduje się w jego obszarze (`inPortal`) lub czy przeszedł przez portal (`throughPortal`).

3. **Rysowanie:**
   - Maski portali i ich obrysy są renderowane w odpowiednich kolorach, co wizualnie odzwierciedla aktywność portalu.





</br>
</br>

---

</br>
</br>





### `resources`

#### Główne definicje
1. **Stałe:**
   - `NUM_SHADERS`: Liczba programów shaderów.
   - `NUM_TEXTURES`: Liczba tekstur.
   - `NUM_MODELS`: Liczba modeli.

2. **Wyliczenia:**
   - `PROGRAM_ID`: Identyfikatory programów shaderów (`PID_PPL` - Phong per-pixel lighting, `PID_NMAP` - Normal mapping).
   - `TEXTURE_ID`: Identyfikatory tekstur (np. `TID_WALL`, `TID_CAKE`).
   - `MODEL_ID`: Identyfikatory modeli (np. `MID_PORTAL_STENCIL`, `MID_CAKE`).

#### Klasa `Resources` **Atrybuty prywatne:**
   - **`GLuint textures[NUM_TEXTURES]`**: Tablica uchwytów do tekstur.
   - **`GLuint programs[NUM_SHADERS]`**: Tablica uchwytów do programów shaderów.
   - **`GLuint models[NUM_MODELS]`**: Tablica uchwytów do list wyświetlania modeli.

#### Implementacje kluczowych metod
1. **`void loadTextures()`**
   - Ładuje tekstury z plików wymienionych w tablicy `texture_files`.
   - Tworzy uchwyty tekstur za pomocą metody `createTexture`.

2. **`GLuint createTexture(const char *filename)`**
   - Wczytuje obraz z pliku za pomocą `stbi_load`.
   - Tworzy teksturę OpenGL z obsługą mipmap i ustawieniami powtarzania w osiach S i T.

3. **`void bindTexture(TEXTURE_ID id)`**
   - Łączy teksturę z odpowiednim uchwytem dla tekstur normalnych (`nmap`) lub standardowych.

4. **`void compileShaders()`**
   - Kompiluje wszystkie programy shaderów:
     - Wczytuje kod z plików shaderów.
     - Kompiluje shadery wierzchołków i fragmentów.
     - Łączy programy shaderów i zapisuje ich uchwyty.

5. **`void enableProgram(PROGRAM_ID pid)`**
   - Aktywuje program shadera o podanym identyfikatorze.
   - Ustawia parametry `tex` (tekstura standardowa) i `nmap` (tekstura normalna).

6. **`void disableProgram()`**
   - Dezaktywuje aktualnie używany program shaderów.

7. **`void compileModels()`**
   - Kompiluje modele (np. stencil dla portalu, obrys portalu i model ciastka) jako listy wyświetlania OpenGL.

8. **`void drawModel(MODEL_ID mid)`**
   - Rysuje model z listy wyświetlania na podstawie identyfikatora `mid`.

9. **`char* readShader(const char *filename)`**
   - Wczytuje zawartość pliku shaderów do bufora w pamięci.

10. **`void printShaderLog` i `void printProgramLog`**
    - Wyświetlają logi błędów z kompilacji shaderów i linkowania programów, aby pomóc w debugowaniu.





</br>
</br>

---

</br>
</br>




### `shot`

#### Atrybuty klasy `Shot`
1. **Stan strzału:**
   - `bool active`: Określa, czy strzał jest aktywny (widoczny i w ruchu).
   - `int id`: Identyfikator portalu, do którego należy strzał (0 dla niebieskiego, 1 dla pomarańczowego).

2. **Pozycja i prędkość:**
   - `float x, y, z`: Pozycja strzału w przestrzeni trójwymiarowej.
   - `float xspeed, yspeed, zspeed`: Wektor prędkości strzału w osiach X, Y i Z.

#### Implementacje kluczowych metod
1. **`void shoot(int id, float x, float y, float z, float xrot, float yrot)`**
   - Aktywuje strzał i ustawia jego pozycję na `(x, y + 1.5, z)` (przesunięcie w osi Y symuluje wystrzał z działa portali).
   - Oblicza prędkości w osiach X, Y i Z na podstawie kierunków `xrot` i `yrot`, korzystając z funkcji trygonometrycznych i stałej prędkości `SHOTSPEED`.

2. **`void update(float dt)`**
   - Zmienia pozycję strzału proporcjonalnie do jego prędkości i czasu `dt`.

3. **`void draw(float xrot, float yrot)`**
   - Renderuje strzał jako sprite z teksturą przypisaną do strzałów (`TID_BALLS`).
   - Rotacja sprite'a jest dostosowana do aktualnego widoku kamery, dzięki czemu sprite zawsze jest zwrócony w stronę gracza.








</br>
</br>

---

</br>
</br>





### `stb_image`

Plik ten zawiera bibliotekę **stb_image**, która jest popularnym, publicznie dostępnym narzędziem do wczytywania obrazów w różnych formatach. Jest to plik źródłowy implementujący funkcje, które umożliwiają łatwe ładowanie obrazów do pamięci w formacie, który można wykorzystać w grach i innych aplikacjach.


### Kluczowe cechy `stb_image.c`

1. **Obsługiwane formaty obrazów:**
   - JPEG (baseline, bez obsługi progresywnej kompresji).
   - PNG (tylko 8-bitowe).
   - TGA (subset, niepełna obsługa).
   - BMP (bez 1-bitowych pikseli i bez RLE).
   - PSD (tylko widok skompozytowany, bez dodatkowych kanałów).
   - GIF (zawsze jako 4-kanałowe RGBA).
   - HDR (format radiance `rgbE`).
   - PIC (Softimage PIC).

2. **Cechy techniczne:**
   - Możliwość wczytywania obrazów z pamięci (`decode from memory`) lub za pomocą plików (`decode through FILE`).
   - Możliwość użycia własnych callbacków do wejścia/wyjścia (`arbitrary I/O callbacks`).
   - Opcjonalna optymalizacja SIMD dla konwersji kolorów (`define STBI_SIMD`).

3. **Definiowanie konfiguracji:**
   - Można wyłączyć obsługę standardowego wejścia/wyjścia przez `#define STBI_NO_STDIO`.
   - Plik oferuje możliwość nadpisania funkcji przetwarzania kolorów i dekompresji.

4. **Public domain:**
   - Kod jest dostępny w domenie publicznej, co oznacza, że można go używać w projektach komercyjnych bez ograniczeń.

### Zastosowanie w projekcie
1. **Ładowanie tekstur:** 
   - W projekcie funkcja `stbi_load` jest używana do wczytywania obrazów tekstur z plików na dysku. 
   - Tekstury są następnie przekształcane w tekstury OpenGL przy użyciu funkcji `glTexImage2D` i powiązane z uchwytami.

2. **Integracja:** 
   - Biblioteka działa jako narzędzie wspierające dla klasy `Resources`, umożliwiając szybkie wczytywanie plików obrazów.

3. **Wszechstronność:** 
   - Dzięki obsłudze różnych formatów obrazów, aplikacja może wykorzystywać różnorodne zasoby graficzne bez potrzeby dodatkowych bibliotek.





</br>
</br>

---

</br>
</br>






### Shadery `nmap.frag` i `nmap.vert`

Te pliki zawierają shadery GLSL (OpenGL Shading Language), które implementują **normal mapping**. Normal mapping to technika oświetleniowa, która używa tekstur normalnych, aby symulować drobne szczegóły geometryczne na powierzchni obiektu, bez dodawania dodatkowych wielokątów.

### `nmap.vert` (Vertex Shader)

#### Główne kroki:
1. **Obliczenie wektora światła:**
   - Wektor od wierzchołka do światła obliczany jest jako różnica między pozycją źródła światła a pozycją wierzchołka.
   - Wektor ten jest następnie transformowany do **przestrzeni tangensowej**, która jest lokalną przestrzenią dla każdego wierzchołka, zależną od jego normalnych, tangensów i bitangensów.

2. **Macierz TBN:**
   - Macierz TBN (Tangent, Bitangent, Normal) przekształca wektory ze światowej przestrzeni do przestrzeni tangensowej.
   - Tangens (`t`), bitangens (`b`) i normalne (`n`) są odpowiednio obliczane i używane do zbudowania macierzy TBN.

3. **Przekazanie danych do fragment shadera:**
   - Wektor światła (`light`) oraz współrzędne tekstury są przekazywane jako zmienne interpolowane (`varying`), aby mogły być używane w fragment shaderze.


### Plik `nmap.frag` (Fragment Shader)

#### Główne kroki:
1. **Uzyskanie normalnych z tekstury normalnej:**
   - Dane normalne są odczytywane z tekstury normalnej (`nmap`), przekształcane z przestrzeni tekstury (0–1) na przestrzeń (-1–1).

2. **Interpolacja wektora światła:**
   - Wektor światła, po interpolacji, jest normalizowany, aby był poprawny w przestrzeni tangensowej.

3. **Obliczenie oświetlenia:**
   - **Ambient lighting:** Bazowe oświetlenie otoczenia obliczane z materiału i źródła światła.
   - **Diffuse lighting:** Światło rozproszone obliczane jako iloczyn skalarny normalnych i wektora światła.

4. **Finalny kolor piksela:**
   - Kolor jest obliczany jako suma światła otoczenia i światła rozproszonego, przemnożona przez kolor tekstury (`texture`).





</br>
</br>

---

</br>
</br>





### Shadery `ppl.frag` i `ppl.vert`

Te shadery implementują **oświetlenie Phonga** w przestrzeni widoku (per-pixel lighting). Jest to klasyczna metoda renderowania, która zapewnia realistyczne efekty oświetleniowe poprzez obliczenia oświetlenia w każdym fragmencie (pikselu) zamiast wierzchołkach.

### `ppl.vert` (Vertex Shader)

#### Główne kroki:
1. **Obliczenie pozycji wierzchołka:**
   - Pozycja wierzchołka jest przekształcana z przestrzeni modelu do przestrzeni widoku za pomocą macierzy `gl_ModelViewMatrix`.

2. **Obliczenie wektora światła:**
   - Wektor od wierzchołka do źródła światła jest obliczany jako różnica między pozycją źródła światła a pozycją wierzchołka.
   - Wektor jest normalizowany.

3. **Przekształcenie wektora normalnego:**
   - Normalne są przekształcane do przestrzeni widoku za pomocą macierzy `gl_NormalMatrix`.

4. **Przekazanie danych:**
   - Wektory `light` i `normal` są przekazywane do fragment shadera jako zmienne interpolowane (`varying`).


### `ppl.frag` (Fragment Shader)

#### Główne kroki:
1. **Normalizacja wektorów:**
   - Wektory `light` i `normal` są normalizowane po interpolacji, aby zapewnić poprawne wyniki obliczeń.

2. **Obliczenie oświetlenia:**
   - **Ambient lighting:** Bazowe oświetlenie otoczenia obliczane jako iloczyn ambientu źródła światła i materiału.
   - **Diffuse lighting:** Światło rozproszone obliczane jako iloczyn skalarny znormalizowanego wektora normalnego i wektora światła, przemnożone przez parametry materiału i światła.

3. **Kombinacja z teksturą:**
   - Finalny kolor piksela to suma ambientu i diffuse, przemnożona przez kolor odczytany z tekstury.