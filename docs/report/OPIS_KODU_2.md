### Podział funkcji według plików:

#### `map`
- **`load(const char *filename)`** – Wczytuje mapę z pliku tekstowego i tworzy listy obiektów.
- **`draw(bool nmap)`** – Renderuje mapę z uwzględnieniem trybu normal mapping.
- **`drawFromPortal(const Portal& portal, bool nmap)`** – Renderuje scenę z perspektywy portalu.
- **`drawBox(Box &b)`** – Rysuje prostokątny obiekt.
- **`drawCake()`** – Rysuje "ciastko" na mapie.
- **`drawLamp()`** – Renderuje lampę jako źródło światła.
- **`collidesWithWall(Box &bbox)`** – Sprawdza kolizję obiektu ze ścianami.
- **`collidesWithAcid(Box &bbox)`** – Sprawdza, czy obiekt wpada do basenu kwasu.
- **`collidesWithCake(Box &bbox)`** – Sprawdza, czy gracz dotarł do "ciastka".
- **`pointInWall(float x, float y, float z, Box *box)`** – Sprawdza, czy dany punkt znajduje się wewnątrz ściany.

---

#### `box`
- **`Box()`** – Konstruktor domyślny, inicjalizuje pusty obiekt.
- **`Box(float x1, float y1, float z1, float x2, float y2, float z2, TEXTURE_ID type)`** – Tworzy prostokąt na podstawie współrzędnych i tekstury.
- **`set(float x1, float y1, float z1, float x2, float y2, float z2, TEXTURE_ID type)`** – Ustawia współrzędne i sortuje je.
- **`collide(const Box &b)`** – Sprawdza, czy dwa prostokąty się przecinają.
- **`collide(float x, float y, float z)`** – Sprawdza, czy dany punkt znajduje się w obiekcie.

---

#### `player`
- **`create(float x, float y, float z)`** – Inicjalizuje pozycję i stan gracza.
- **`update(float dt, bool *keystates, float mousedx, float mousedy, Map &map)`** – Aktualizuje pozycję i interakcję gracza z otoczeniem.
- **`mousePressed(int button)`** – Obsługuje strzały portali przy użyciu myszy.
- **`setView()`** – Aktualizuje kamerę na podstawie pozycji gracza.
- **`portalsActive()`** – Sprawdza, czy oba portale są aktywne.
- **`drawPortalStencils()`** – Rysuje maski portali.
- **`drawPortalOutlines()`** – Rysuje obrysy portali.
- **`drawShots()`** – Rysuje strzały portali.
- **`respawn()`** – Resetuje gracza po śmierci.

---

#### `portal`
- **`place(float x, float y, float z, PORTAL_DIR dir, Map& map)`** – Ustawia portal na danej powierzchni.
- **`placeOnBox(Box &box, float hitx, float hity, float hitz, Map& map)`** – Dopasowuje portal do ściany obiektu.
- **`inPortal(Box &box)`** – Sprawdza, czy obiekt znajduje się w portalu.
- **`throughPortal(float r, float s, float t)`** – Sprawdza, czy gracz przeszedł przez portal.
- **`disable()`** – Dezaktywuje portal.
- **`drawStencil()`** – Rysuje maskę portalu.
- **`drawOutline(PORTAL_COLOR color)`** – Rysuje obrys portalu w odpowiednim kolorze.

---

#### `resources`
- **`loadTextures()`** – Wczytuje tekstury z plików.
- **`createTexture(const char *filename)`** – Tworzy teksturę OpenGL.
- **`bindTexture(TEXTURE_ID id)`** – Przypisuje teksturę do obiektu.
- **`compileShaders()`** – Kompiluje programy shaderów.
- **`enableProgram(PROGRAM_ID pid)`** – Aktywuje wybrany program shaderów.
- **`disableProgram()`** – Dezaktywuje shadery.
- **`compileModels()`** – Kompiluje modele 3D.
- **`drawModel(MODEL_ID mid)`** – Renderuje model na podstawie identyfikatora.

---

#### `shot`
- **`shoot(int id, float x, float y, float z, float xrot, float yrot)`** – Aktywuje strzał portalu i ustawia jego kierunek.
- **`update(float dt)`** – Aktualizuje pozycję strzału.
- **`draw(float xrot, float yrot)`** – Renderuje strzał portalu.

---

#### `main`
- **`update(int value)`** – Aktualizuje stan gry i gracza.
- **`nextLevel()`** – Wczytuje kolejny poziom.
- **`draw()`** – Renderuje scenę.
- **`drawPortals()`** – Renderuje portale.
- **`drawOverlay()`** – Renderuje interfejs użytkownika.
- **`mouse_moved(int x, int y)`** – Obsługuje ruch myszy.
- **`mouse_pressed(int button, int state, int x, int y)`** – Reaguje na kliknięcia myszy.
- **`key_down(unsigned char key, int x, int y)`** – Obsługuje naciśnięcia klawiszy.
- **`key_up(unsigned char key, int x, int y)`** – Obsługuje zwolnienie klawiszy.
- **`resize(int w, int h)`** – Dostosowuje okno gry.
- **`setup(int *argc, char **argv)`** – Inicjalizuje grę i OpenGL.
- **`main(int argc, char **argv)`** – Uruchamia pętlę główną gry.