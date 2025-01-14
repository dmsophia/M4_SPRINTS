//incluir componente dos botões e bibliotecas no tabuleiro
import React, { Component } from 'react';
import Square from './square'; 

export default class Board extends Component {
    renderSquare(i){
        return <Square value={this.props.squares[i]}
        onClick={()=>this.props.onClick(i)}
        />
    }
    /*As divs abaixo, com parâmetros numéricos, 
    irão servir para calcular o ganhador do jogo da velha*/
    render() {
        return (
            <div>
                <div className="border-row">
                    {this.renderSquare(0)}
                    {this.renderSquare(1)}
                    {this.renderSquare(2)}
                </div>
                <div className="border-row">
                    {this.renderSquare(3)}
                    {this.renderSquare(4)}
                    {this.renderSquare(5)}
                </div>
                <div className="border-row">
                    {this.renderSquare(6)}
                    {this.renderSquare(7)}
                    {this.renderSquare(8)}
                </div>
                
            </div>
        )
    }
}