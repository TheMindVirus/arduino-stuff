#define TYPE(CARD)    (CARD & 0x0F)
#define CHROMA(CARD)  (CARD & 0xF0)

#define SET_RED(CARD) (CARD + 0x10)
#define SET_YLW(CARD) (CARD + 0x20)
#define SET_GRN(CARD) (CARD + 0x40)
#define SET_BLU(CARD) (CARD + 0x80)
#define SET_NUL(CARD) (CARD &= 0xF0)

#define IS_RED(CARD) ((CARD & 0x10) != 0)
#define IS_YLW(CARD) ((CARD & 0x20) != 0)
#define IS_GRN(CARD) ((CARD & 0x40) != 0)
#define IS_BLU(CARD) ((CARD & 0x80) != 0)
#define IS_NUL(CARD)  (CHROMA(CARD) == 0)

enum CARD { CARD_0 = 0, CARD_1, CARD_2, CARD_3, CARD_4, CARD_5, CARD_6, CARD_7, CARD_8, CARD_9, CARD_SKIP, CARD_SWAP, CARD_ADD2, CARD_DRAW, CARD_ADD4, CARD_NULL };
uint8_t PILE[] =
{
    SET_RED(CARD_0), SET_RED(CARD_1), SET_RED(CARD_2), SET_RED(CARD_3), SET_RED(CARD_4), SET_RED(CARD_5), SET_RED(CARD_6), SET_RED(CARD_7), SET_RED(CARD_8), SET_RED(CARD_9), SET_RED(CARD_SKIP), SET_RED(CARD_SWAP), SET_RED(CARD_ADD2), CARD_DRAW,
    SET_YLW(CARD_0), SET_YLW(CARD_1), SET_YLW(CARD_2), SET_YLW(CARD_3), SET_YLW(CARD_4), SET_YLW(CARD_5), SET_YLW(CARD_6), SET_YLW(CARD_7), SET_YLW(CARD_8), SET_YLW(CARD_9), SET_YLW(CARD_SKIP), SET_YLW(CARD_SWAP), SET_YLW(CARD_ADD2), CARD_DRAW,
    SET_GRN(CARD_0), SET_GRN(CARD_1), SET_GRN(CARD_2), SET_GRN(CARD_3), SET_GRN(CARD_4), SET_GRN(CARD_5), SET_GRN(CARD_6), SET_GRN(CARD_7), SET_GRN(CARD_8), SET_GRN(CARD_9), SET_GRN(CARD_SKIP), SET_GRN(CARD_SWAP), SET_GRN(CARD_ADD2), CARD_DRAW,
    SET_BLU(CARD_0), SET_BLU(CARD_1), SET_BLU(CARD_2), SET_BLU(CARD_3), SET_BLU(CARD_4), SET_BLU(CARD_5), SET_BLU(CARD_6), SET_BLU(CARD_7), SET_BLU(CARD_8), SET_BLU(CARD_9), SET_BLU(CARD_SKIP), SET_BLU(CARD_SWAP), SET_BLU(CARD_ADD2), CARD_DRAW,
    
    SET_RED(CARD_NULL), SET_RED(CARD_1), SET_RED(CARD_2), SET_RED(CARD_3), SET_RED(CARD_4), SET_RED(CARD_5), SET_RED(CARD_6), SET_RED(CARD_7), SET_RED(CARD_8), SET_RED(CARD_9), SET_RED(CARD_SKIP), SET_RED(CARD_SWAP), SET_RED(CARD_ADD2), CARD_ADD4,
    SET_YLW(CARD_NULL), SET_YLW(CARD_1), SET_YLW(CARD_2), SET_YLW(CARD_3), SET_YLW(CARD_4), SET_YLW(CARD_5), SET_YLW(CARD_6), SET_YLW(CARD_7), SET_YLW(CARD_8), SET_YLW(CARD_9), SET_YLW(CARD_SKIP), SET_YLW(CARD_SWAP), SET_YLW(CARD_ADD2), CARD_ADD4,
    SET_GRN(CARD_NULL), SET_GRN(CARD_1), SET_GRN(CARD_2), SET_GRN(CARD_3), SET_GRN(CARD_4), SET_GRN(CARD_5), SET_GRN(CARD_6), SET_GRN(CARD_7), SET_GRN(CARD_8), SET_GRN(CARD_9), SET_GRN(CARD_SKIP), SET_GRN(CARD_SWAP), SET_GRN(CARD_ADD2), CARD_ADD4,
    SET_BLU(CARD_NULL), SET_BLU(CARD_1), SET_BLU(CARD_2), SET_BLU(CARD_3), SET_BLU(CARD_4), SET_BLU(CARD_5), SET_BLU(CARD_6), SET_BLU(CARD_7), SET_BLU(CARD_8), SET_BLU(CARD_9), SET_BLU(CARD_SKIP), SET_BLU(CARD_SWAP), SET_BLU(CARD_ADD2), CARD_ADD4,
};
const uint8_t MAX_COUNT = sizeof(PILE);
const uint8_t VARIANTS = 4;
const uint8_t PLAYERS = 4;
const uint8_t STARTING = 7;

const int TIMEOUT = 10; //3000;
const uint8_t TIMEOUT_HI = (TIMEOUT & 0xFF00) >> 8;
const uint8_t TIMEOUT_LO = TIMEOUT & 0xFF;

uint8_t pile[MAX_COUNT] = {};
uint8_t hand[PLAYERS][MAX_COUNT] = {};

uint8_t pile_count = 0;
uint8_t hand_count[PLAYERS] = {};

uint8_t game = 0;
uint8_t turn = 0;
bool reverse = false;
bool skip = false;
uint8_t card = 0;

double seed(double n = 0);
double shuffle(double n = 0);
double load_pile(double n = 0);
double empty_hands(double n = 0);
double fill_hands(double n = 0);
double draw_card(double n = 0);
double place_card(double n = 0);
double show_cards(double n = 0);
double next_turn(double n = 0);

double seed(double n = 0)
{
    analogWrite(9, 127);
    analogWrite(10, 128);
    analogWrite(11, 129);
    double a = n;
    a += analogRead(9);
    a += analogRead(10);
    a += analogRead(11);
    a /= 3;
    randomSeed(a);
    return a;
}

double shuffle(double n = 0)
{
    uint8_t tmp = 0;
    uint8_t idx1 = 0;
    uint8_t idx2 = 0;
        
    for (uint8_t i = 0; i < pile_count; ++i)
    {
        seed(seed(seed()));
        idx1 = random(0, pile_count);
        seed(seed(seed()));
        idx2 = random(0, pile_count);
        tmp = pile[idx1];
        pile[idx1] = pile[idx2];
        pile[idx2] = tmp;
    }
    
    uint8_t j = 0;
    uint8_t i = 0;
    for (uint8_t x = pile_count; x > 0; --x)
    {
        i = x - 1;
        tmp = pile[j];
        pile[j] = pile[i];
        pile[i] = tmp;
        ++j;
        if (j >= pile_count / 2) { break; }
    }
    if (n <= 1) { return 0.0f; }
    return shuffle(n - 1);
}

double load_pile(double n = 0)
{
    uint8_t j = 0;
    for (uint8_t i = 0; i < MAX_COUNT; ++i)
    {
        if (TYPE(PILE[i]) != CARD_NULL) { pile[j] = PILE[i]; ++j; }
    }
    pile_count = j;
    return pile_count;
}

double empty_hands(double n = 0)
{
    for (int j = 0; j < PLAYERS; ++j)
    {
        for (int i = 0; i < MAX_COUNT; ++i) { hand[j][i] = 0; }
        hand_count[j] = 0;
    }
    return PLAYERS;
}

double fill_hands(double n = 0)
{
    for (int j = 0; j < PLAYERS; ++j)
    {
        for (int i = 0; i < STARTING; ++i) { draw_card(j); }
        hand_count[j] = STARTING;
    }
    return PLAYERS;
}

double draw_card(double n = 0)
{
    if (pile_count == 0) { Serial.println("[INFO]: DRAW"); ++game; setup(); }
    uint8_t x = ((uint8_t)n) % PLAYERS;
    ++hand_count[x];
    hand[x][hand_count[x] - 1] = pile[pile_count - 1];
    pile[pile_count - 1] = 0;
    --pile_count;
    return x;
}

double place_card(double n = 0)
{
    uint8_t x = (uint8_t)n % PLAYERS;
    if (skip == true) { skip = false; next_turn(); return x; }
    for (int i = 0; i < hand_count[x]; ++i)
    {
        if ((CHROMA(hand[x][i]) == CHROMA(card))
        ||  (IS_NUL(hand[x][i]) || IS_NUL(card)))
        {
            card = hand[x][i];
            if (TYPE(card) == CARD_SWAP) { reverse = !reverse; }
            if (TYPE(card) == CARD_SKIP) { skip = true; }
            if ((TYPE(card) == CARD_DRAW) || (TYPE(card) == CARD_ADD4))
            {
                seed(seed(seed()));
                uint8_t c = random(0, VARIANTS) % VARIANTS;
                switch (c)
                {
                    case(0): { card = SET_RED(card); } break;
                    case(1): { card = SET_YLW(card); } break;
                    case(2): { card = SET_GRN(card); } break;
                    case(3): { card = SET_BLU(card); } break;
                    default: { card = SET_NUL(card); } break;
                }
            }
            for (int j = i; j < hand_count[x]; ++j)
            {
                hand[x][j] = hand[x][j + 1];
            }
            hand[x][hand_count[x] - 1] = 0;
            --hand_count[x];
            if (hand_count[x] == 0)
            {
                Serial.print("[INFO]: Player ");
                Serial.print(((int)x) + 1);
                Serial.println(" Wins!");
                ++game; setup();
            }
            return x;
        }
    }
    if (TYPE(card) == CARD_ADD2) { draw_card(x); draw_card(x); return x; }
    if (TYPE(card) == CARD_ADD4) { draw_card(x); draw_card(x); draw_card(x); draw_card(x); return x; }
    draw_card(x);
    return x;
}

double show_cards(double n = 0)
{
    Serial.print("[GAME]: ");
    Serial.println(game + 1);
    Serial.print("[TURN]: ");
    Serial.println(turn + 1);
    Serial.print("[CARD]: ");
    Serial.println(card + 0);
    Serial.print("[PILE]: ");
    for (uint8_t i = 0; i < pile_count; ++i)
    {
        Serial.print(pile[i]);
        Serial.print(", ");
    }
    Serial.println();
    for (uint8_t j = 0; j < PLAYERS; ++j)
    {
        Serial.print("[HAND]: ");
        for (uint8_t i = 0; i < hand_count[j]; ++i)
        {
            Serial.print(hand[j][i]);
            Serial.print(", ");
        }
        Serial.println();
    }
    return 0.0f;
}

double next_turn(double n = 0)
{
    if (!reverse)
    {
        ++turn;
        if (turn >= PLAYERS) { turn = 0; }
    }
    else
    {
        if (turn > 0) { --turn; }
        else { turn = PLAYERS - 1; }
    }
    return turn;
}

void setup()
{
    if (game == 0) { Serial.begin(115200); }
    Serial.println("<<<UNO>>>");
    Serial.println("[INFO]: Game Now Loading...");
    Serial.println("[INFO]: (shuffling might need a few seconds)");
    load_pile();
    shuffle(pile_count / 2);
    empty_hands();
    fill_hands();
    turn = 0;
    show_cards();
    delay((TIMEOUT_HI << 8) + TIMEOUT_LO);
}

void loop()
{
    place_card(turn);
    show_cards();
    delay(TIMEOUT);
    next_turn();
}
