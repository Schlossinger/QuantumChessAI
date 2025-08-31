# Der Parallelzug-Algorithmus (Muster-Methode)

**Eine neue Dimension für Schach-KI und Analyse**  
*Von Dominik Schloss (Schlossinger)*

---

## 🚀 Einleitung

Stell dir vor, Schachzüge würden nicht mehr einzeln, sondern als **fließende Muster** betrachtet, die sich gleichzeitig über das ganze Brett verteilen.  
Genau das ermöglicht der **Parallelzug-Algorithmus**, auch „Muster-Methode“ genannt: Eine innovative Methode, die klassische Zugbaum-Logik durch verteilte **Figurenanteile** ersetzt – und so ganz neue Analysen, KIs und Visualisierungen ermöglicht.

---

## 🔬 Grundprinzip: Figurenanteile statt einzelner Züge

- **Alle Figuren starten mit 100% Aufenthaltsanteil auf ihrem Feld.**
- Bei jedem Halbzug wird der Anteil entsprechend der Zugmöglichkeiten über das Brett **verteilt** – wie eine Welle, die sich ausbreitet.
- **Mehrere Figuren** (auch unterschiedlicher Parteien) können Anteile auf demselben Feld halten.
- Für jedes der 64 Felder werden **bis zu 32 Figurenanteile** geführt (alle Figuren beider Seiten).
- Zusätzlich werden für jedes Feld Summen gebildet:
  1. **Summe der weißen Figurenanteile**
  2. **Summe der schwarzen Figurenanteile**
  3. **Gesamtsumme aller Figurenanteile**
  4. **Anteil „leeres Feld“** (100% minus Gesamtsumme der Figurenanteile)

**Die Summe aller Figurenanteile + Anteil „leeres Feld“ ergibt für jedes Feld stets 100%.**

---

## 🧩 Schrittweise Vorgehensweise

1. **Alle legalen Züge berechnen** (wie bei Minimax)
2. **Figurenanteile anteilig auf Ziel-Felder verteilen**  
   - z. B. bei 4 möglichen Zügen: je 25% auf jedes Zielfeld
3. **Iteration über Halbzüge:**  
   - Mit jedem Halbzug verteilen sich die Anteile weiter über das Brett
   - Felder können Anteile von mehreren Figuren und Seiten zugleich halten
   - Die Muster der Figurenanteile beeinflussen sich gegenseitig (Verstärkung, Abschwächung, „Interferenzen“)
4. **Musteranalyse:**  
   - Die Endverteilung der Figurenanteile dient als Basis für die Bewertung von Zügen
   - Ziel: Denjenigen Ausgangszug finden, der im Verlauf die günstigsten Muster erzeugt

---

## 🧮 Praxisbeispiel: Eröffnung durch Weiß

Schauen wir uns eine typische Schach-Eröffnung durch Weiß an:

Zu Beginn der Partie können sich alle 8 weißen Bauern und die 2 Springer bewegen. Jeder Bauer hat genau zwei Zugmöglichkeiten (von Reihe 2 auf Reihe 3 oder 4), und jeder Springer ebenfalls zwei mögliche Felder.

**Berechnung der Zugmöglichkeiten:**  
- 8 Bauern × 2 Züge = **16 Züge**  
- 2 Springer × 2 Züge = **4 Züge**  
- Gesamt: **20 mögliche Züge**

**Verteilung der Figurenanteile:**  
- Jede Figur startet mit 100 % auf ihrem Feld.  
- Diese 100 % verteilen sich gleichmäßig auf alle möglichen Zielfelder:
  - **Pro möglichem Zug:** 100 % ÷ 20 Züge = **5 % pro Zug**
- **Für jede einzelne Figur** gilt bei zwei Zugmöglichkeiten:  
  - **2 Züge × 5 % = 10 %** verteilen sich auf die beiden Zielfelder.  
  - Der **Restanteil (90 %) bleibt auf dem Ursprungsfeld** stehen.

**Ergebnis:**  
- Jedes Zielfeld bekommt jeweils 5 % Figurenanteil hinzu.  
- Die Ausgangsfelder behalten zunächst 90 % des ursprünglichen Anteils.  
- Dies erzeugt dynamische Muster, welche die Grundlage weiterer Iterationen und Analysen bilden.

**Mathematische Kurzformel:**  
Für eine Figur mit \( n \) Zugmöglichkeiten und Aufenthaltsanteil \( A \):

- Anteil pro Zielfeld: \( \frac{A}{n} \)  
- Verbleibender Anteil auf dem Ursprungsfeld: \( A - n \times \frac{A}{n} \)

---

## 🎯 Vorteile & Potenziale

- **Weniger redundante Berechnungen** als klassische Zugbäume
- **Dynamische Bewertung:** Züge werden als Muster-Verläufe analysiert, nicht nur als Einzelpositionen
- **Ideal kombinierbar mit KI & Machine Learning** (z. B. neuronale Netze, stochastische Verfahren)
- **Neue Visualisierungen:** Heatmaps, Anteilskarten & dynamische Musteranalysen

---

## ⚙️ Mathematische Grundstruktur

- **64 Felder × max. 32 Figurenanteile** = 2048 Variablen pro Iterationsschritt
- **Jeder Anteil ist eine Zahl von 0%–100%**, Summe aller Anteile je Feld ≤ 100%
- **Vier Summen pro Feld:** weiß, schwarz, gesamt, leer
- **Iterative Verteilung**: Die Verteilungsmatrix wird bei jedem Halbzug aktualisiert

---

## 📊 Visualisierungen

*Hier könnten Beispiel-Heatmaps oder Diagramme folgen!*  
*(Bitte ein PNG, SVG oder animiertes GIF als `/img/heatmap1.png` einfügen)*

---

## 🗣️ Call to Action

**Lust auf Diskussion, Kritik, Verbesserung oder Kooperation?**  
**Kommentiere, teile, forke oder schreib mir –**  
**Gemeinsam heben wir das Schachbrett auf ein neues Level!**

---

