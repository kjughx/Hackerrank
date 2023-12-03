#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Spell {
  private:
    string scrollName;

  public:
    Spell() : scrollName("") {}
    Spell(string name) : scrollName(name) {}
    virtual ~Spell() {}
    string revealScrollName() { return scrollName; }
};

class Fireball : public Spell {
  private:
    int power;

  public:
    Fireball(int power) : power(power) {}
    void revealFirepower() { cout << "Fireball: " << power << endl; }
};

class Frostbite : public Spell {
  private:
    int power;

  public:
    Frostbite(int power) : power(power) {}
    void revealFrostpower() { cout << "Frostbite: " << power << endl; }
};

class Thunderstorm : public Spell {
  private:
    int power;

  public:
    Thunderstorm(int power) : power(power) {}
    void revealThunderpower() { cout << "Thunderstorm: " << power << endl; }
};

class Waterbolt : public Spell {
  private:
    int power;

  public:
    Waterbolt(int power) : power(power) {}
    void revealWaterpower() { cout << "Waterbolt: " << power << endl; }
};

class SpellJournal {
  public:
    static string journal;
    static string read() { return journal; }
};
string SpellJournal::journal = "";

std::unordered_set<string> subsequence(string str) {
    std::unordered_set<string> set;
    for (int i = 0; i < str.length(); i++) {
        for (int j = str.length(); j > i; j--) {
            string sub_str = str.substr(i, j);
            set.insert(sub_str);
            for (int k = 1; k < sub_str.length(); k++) {
                string sb = sub_str;
                sb.erase(sb.begin() + k);
                subsequence(sb);
            }
        }
    }
    return set;
}

void counterspell(Spell* spell) {
    if (Fireball* s = dynamic_cast<Fireball*>(spell); s != nullptr)
        s->revealFirepower();
    else if (Waterbolt* s = dynamic_cast<Waterbolt*>(spell); s != nullptr)
        s->revealWaterpower();
    else if (Thunderstorm* s = dynamic_cast<Thunderstorm*>(spell); s != nullptr)
        s->revealThunderpower();
    else if (Frostbite* s = dynamic_cast<Frostbite*>(spell); s != nullptr)
        s->revealFrostpower();
    else {
        string spell_name = spell->revealScrollName();
        string journal_entry = SpellJournal::read();
        std::vector<std::vector<int>> table(spell_name.length() + 1, std::vector<int>(journal_entry.length() + 1, 0));
        if (spell_name == journal_entry){
            cout << spell_name.length() << endl;
        } else {
            for(int i = 0; i < spell_name.length(); ++i) {
                for(int j = 0; j < journal_entry.length(); ++j) {
                    if (spell_name[i] == journal_entry[j])
                        table[i+1][j+1] = table[i][j] + 1;
                    else {
                        table[i+1][j+1] = max(table[i+1][j], table[i][j+1]);
                    }
                }
            }
            cout << table[spell_name.length()][journal_entry.length()] << endl;
        }
    }
}

class Wizard {
  public:
    Spell* cast() {
        Spell* spell;
        string s;
        cin >> s;
        int power;
        cin >> power;
        if (s == "fire") {
            spell = new Fireball(power);
        } else if (s == "frost") {
            spell = new Frostbite(power);
        } else if (s == "water") {
            spell = new Waterbolt(power);
        } else if (s == "thunder") {
            spell = new Thunderstorm(power);
        } else {
            spell = new Spell(s);
            cin >> SpellJournal::journal;
        }
        return spell;
    }
};

int main() {
    int T;
    cin >> T;
    Wizard Arawn;
    while (T--) {
        Spell* spell = Arawn.cast();
        counterspell(spell);
    }
    return 0;
}
