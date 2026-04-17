<!DOCTYPE html>
<html>
<head>
    <title>Memory Game (C++ Logic Style)</title>

    <style>
        body {
            background: #1e1e2f;
            color: white;
            text-align: center;
            font-family: Arial;
        }

        h1 {
            margin-top: 20px;
        }

        .stats {
            margin: 10px;
            font-size: 18px;
        }

        .game {
            display: grid;
            grid-template-columns: repeat(4, 100px);
            gap: 10px;
            justify-content: center;
            margin-top: 20px;
        }

        .card {
            width: 100px;
            height: 100px;
            background: #00adb5;
            display: flex;
            justify-content: center;
            align-items: center;
            font-size: 30px;
            cursor: pointer;
            border-radius: 10px;
        }

        .flipped {
            background: #eeeeee;
            color: black;
        }

        button {
            margin-top: 15px;
            padding: 10px 20px;
            background: #00adb5;
            border: none;
            color: white;
            cursor: pointer;
        }
    </style>
</head>

<body>

<h1>🧠 Memory Game</h1>

<div class="stats">
    ⏱️ Time: <span id="time">0</span> sec |
    ⭐ Score: <span id="score">0</span>
</div>

<div class="game" id="game"></div>

<button onclick="restartGame()">Restart</button>

<script>

// ============================
// 🔥 C++ STYLE LOGIC SECTION
// ============================

// C++ style array (vector equivalent)
let cards = ['A','B','C','D','A','B','C','D'];

// Shuffle function (like C++)
function shuffleCards() {
    cards.sort(() => Math.random() - 0.5);
}

// Match function (same as C++)
function checkMatch(i, j) {
    return cards[i] === cards[j];
}

// ============================
// 🎮 GAME VARIABLES
// ============================

let firstIndex = -1;
let secondIndex = -1;
let lock = false;
let score = 0;
let time = 0;

// ============================
// ⏱️ TIMER
// ============================

let timer = setInterval(() => {
    time++;
    document.getElementById("time").innerText = time;
}, 1000);

// ============================
// 🧩 INITIALIZE GAME
// ============================

shuffleCards();

const game = document.getElementById("game");

// Create cards
cards.forEach((val, index) => {
    let card = document.createElement("div");
    card.className = "card";
    card.dataset.index = index;

    card.onclick = () => flipCard(card, index);

    game.appendChild(card);
});

// ============================
// 🔄 FLIP LOGIC
// ============================

function flipCard(card, index) {
    if (lock || card.classList.contains("flipped")) return;

    card.innerText = cards[index];
    card.classList.add("flipped");

    if (firstIndex === -1) {
        firstIndex = index;
    } else {
        secondIndex = index;
        lock = true;

        // Check match (C++ logic)
        if (checkMatch(firstIndex, secondIndex)) {
            score++;
            document.getElementById("score").innerText = score;

            firstIndex = -1;
            secondIndex = -1;
            lock = false;

            // 🎉 Win condition
            if (score === cards.length / 2) {
                setTimeout(() => {
                    alert("🎉 You Win! Time: " + time + " sec");
                }, 300);
            }

        } else {
            setTimeout(() => {
                let allCards = document.querySelectorAll(".card");

                allCards[firstIndex].innerText = "";
                allCards[secondIndex].innerText = "";

                allCards[firstIndex].classList.remove("flipped");
                allCards[secondIndex].classList.remove("flipped");

                firstIndex = -1;
                secondIndex = -1;
                lock = false;
            }, 800);
        }
    }
}

// ============================
// 🔁 RESTART GAME
// ============================

function restartGame() {
    location.reload();
}

</script>

</body>
</html>