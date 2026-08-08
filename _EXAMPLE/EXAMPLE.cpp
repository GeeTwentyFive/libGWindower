#include "../include/GWindower.hpp"

int main() {
        GWindower gw{1280, 720, 4, 6};

        while (gw.Update()) { if (gw.key_states[GWindower::KEY_ESCAPE]) break;
                // ...
        }

        return 0;
}