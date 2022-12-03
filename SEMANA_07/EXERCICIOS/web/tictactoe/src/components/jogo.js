import React, { Component } from 'react'
import Board from './tabuleiro';
import axios from 'axios'

export default class Game extends Component {
    constructor(props) {
        super(props);
        /*Estabalece os estados iniciais (default) do jogo, sendo o jogador X o primeiro a jogar, 
        os passos, etapas do jogo, que se iniciam em 0 e o histórico, para saber quem é o próximo jogador*/
        this.state = {
            xIsNext: true,
            stepNumber: 0,
            history: [
                { squares: Array(9).fill(null) } /*O histórico é um array de 9 'passos' que são nulos no começo, 
                pois nenhum jogador jogou ainda*/
            ]
        }
    }
    jumpTo(step){
        this.setState({
            stepNumber: step,
            xIsNext: (step%2)===0
        })
    }
/* A função abaixo define o conceito core do jogo da velha, definindo o histórico, a jogada mais recente (current) 
salva no histórico e o comando de quem é o próximo jogador (X ou O)*/
    handleClick(i) {
        const history = this.state.history.slice(0, this.state.stepNumber + 1);
        const current = history[history.length - 1];
        const squares = current.squares.slice();
        const winner = calculateWinner(squares);
        //Aqui não deixa o próximo jogador mudar o valor de um quadrado caso já esteja preenchido
        if (winner || squares[i]) {
            return;
        }
        squares[i] = this.state.xIsNext ? 'X' : 'O';
        this.setState({
            history: history.concat({
                squares: squares
            }),
            xIsNext: !this.state.xIsNext,
            stepNumber: history.length
        });

    }

    render() {
        //Definindo as constantes do histórico, que controla as jogadas
        const history = this.state.history;
        const current = history[this.state.stepNumber];
        const winner = calculateWinner(current.squares);
        const moves = history.map((step, move) => {
            const desc = move ? 'Go to #' + move : 'Start the Game';
            return (
                <li key={move}>
                    <button onClick={() => { this.jumpTo(move) }}>
                        {desc}
                    </button>
                </li>
            )
        });
        let status;
        if (winner) {
            status = 'Winner is ' + winner;
            /*Para fazer com que o led vermelho ligue quando o jogador X ganhar, usamos a 
            biblioteca axios para enviar a informação ao ESP pelo seu IP e rota estabelecidos,
             a mesma coisa é feita com o Y*/
            if (winner == "X"){
                axios.get("http://10.128.65.199:80/x")
            }
            if (winner == "O"){
                axios.get("http://10.128.65.199:80/o")
            }
        } else {
            status = 'Next Player is ' + (this.state.xIsNext ? 'X' : 'O');
        }


        return (
            <div className="game">
                <div className="game-board">
                    <Board onClick={(i) => this.handleClick(i)}
                        squares={current.squares} />
                </div>
                <div className="game-info">
                    <div>{status}</div>
                    <ul>{moves}</ul>
                </div>

            </div>
        )
    }
}
// Função que calcula quem ganhou o jogo e retorna o vencedor, ou empate
function calculateWinner(squares) {
    const lines = [
        [0, 1, 2],
        [3, 4, 5],
        [6, 7, 8],
        [0, 3, 6],
        [1, 4, 7],
        [2, 5, 8],
        [0, 4, 8],
        [2, 4, 6]
    ];

    for (let i = 0; i < lines.length; i++) {
        const [a, b, c] = lines[i];
        if (squares[a] && squares[a] === squares[b] && squares[b] === squares[c]) {
            return squares[a];
        }
    }

    return null;
}