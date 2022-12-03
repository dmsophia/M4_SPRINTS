import React from 'react'
/*Criar o componente de "botões" do jogo da velha, oa quadrados que
são X ou O a depender do jogador que está jogando*/
export default function Square(props) {
    return (
        <button className="square" onClick={props.onClick}>
            {props.value}
        </button>
    )
}