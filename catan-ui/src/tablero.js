import React, { Component } from 'react';
import { Tile } from './tile';
import { Vertice } from './vertice';
import { Arista } from './arista';
import { Grid, Col, Row } from 'react-bootstrap';

export class Tablero extends Component {
  render() {
    return (
      <div>
        <div className="row">
          <div className="col-xs-3"/>
          <Vertice idx={0} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={1} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={2} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
        </div>
        <div className="row">
          <div className="col-xs-3"/>
          <Arista origen={0} destino={3} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={0} destino={4} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={1} destino={4} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={1} destino={5} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={2} destino={5} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={2} destino={6} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
        </div>
        <div className="row">
          <div className="col-xs-2"/>
          <Vertice idx={3} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={4} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={5} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={6} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
        </div>
        <div className="row">
          <div className="col-xs-3"/>
          <Col xs={2}>
            <Arista origen={3} destino={7} game={this.props.game}
              cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
            />
            <Tile idx={0} game={this.props.game}
              cambiarTerreno={(idx, val) => this.props.cambiarTerreno(idx, val)}
              cambiarNumero={(idx, val) => this.props.cambiarNumero(idx, val)}
            />
            </Col>
          <Col xs={2}>
            <Arista origen={4} destino={8} game={this.props.game}
              cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
            />
            <Tile idx={1} game={this.props.game}
              cambiarTerreno={(idx, val) => this.props.cambiarTerreno(idx, val)}
              cambiarNumero={(idx, val) => this.props.cambiarNumero(idx, val)}
            />
            </Col>
          <Col xs={2}>
            <Arista origen={5} destino={9} game={this.props.game}
              cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
            />
            <Tile idx={2} game={this.props.game}
              cambiarTerreno={(idx, val) => this.props.cambiarTerreno(idx, val)}
              cambiarNumero={(idx, val) => this.props.cambiarNumero(idx, val)}
            />
          </Col>
          <Col xs={2}>
            <Arista origen={6} destino={10} game={this.props.game}
              cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
            />
          </Col>
        </div>
        <div className="row">
          <div className="col-xs-2"/>
          <Vertice idx={7} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={8} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={9} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={10} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
        </div>
        <div className="row">
          <div className="col-xs-2"/>
          <Arista origen={7} destino={11} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={7} destino={12} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={8} destino={12} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={8} destino={13} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={9} destino={13} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={9} destino={14} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={10} destino={14} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={10} destino={15} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
        </div>
        <div className="row">
          <div className="col-xs-1"/>
          <Vertice idx={11} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={12} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={13} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={14} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={15} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
        </div>
        <div className="row">
          <div className="col-xs-2"/>
          <Col xs={2}>
            <Arista origen={11} destino={16} game={this.props.game}
              cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
            />
            <Tile idx={3} game={this.props.game}
              cambiarTerreno={(idx, val) => this.props.cambiarTerreno(idx, val)}
              cambiarNumero={(idx, val) => this.props.cambiarNumero(idx, val)}
            />
          </Col>
          <Col xs={2}>
            <Arista origen={12} destino={17} game={this.props.game}
              cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
            />
            <Tile idx={4} game={this.props.game}
              cambiarTerreno={(idx, val) => this.props.cambiarTerreno(idx, val)}
              cambiarNumero={(idx, val) => this.props.cambiarNumero(idx, val)}
            />
          </Col>
          <Col xs={2}>
            <Arista origen={13} destino={18} game={this.props.game}
              cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
            />
            <Tile idx={5} game={this.props.game}
              cambiarTerreno={(idx, val) => this.props.cambiarTerreno(idx, val)}
              cambiarNumero={(idx, val) => this.props.cambiarNumero(idx, val)}
            />
          </Col>
          <Col xs={2}>
            <Arista origen={14} destino={19} game={this.props.game}
              cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
            />
            <Tile idx={6} game={this.props.game}
              cambiarTerreno={(idx, val) => this.props.cambiarTerreno(idx, val)}
              cambiarNumero={(idx, val) => this.props.cambiarNumero(idx, val)}
            />
          </Col>
          <Col xs={2}>
            <Arista origen={15} destino={20} game={this.props.game}
              cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
            />
          </Col>
        </div>
        <div className="row">
          <div className="col-xs-1"/>
          <Vertice idx={16} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={17} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={18} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={19} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={20} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
        </div>
        <div className="row">
          <div className="col-xs-1"/>
          <Arista origen={16} destino={21} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={16} destino={22} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={17} destino={22} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={17} destino={23} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={18} destino={23} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={18} destino={24} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={19} destino={24} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={19} destino={25} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={20} destino={25} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={20} destino={26} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
        </div>
        <div className="row">
          <Vertice idx={21} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={22} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={23} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={24} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={25} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={26} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
        </div>
        <div className="row">
          <div className="col-xs-1"/>
          <Col xs={2}>
            <Arista origen={21} destino={27} game={this.props.game}
              cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
            />
            <Tile idx={7} game={this.props.game}
              cambiarTerreno={(idx, val) => this.props.cambiarTerreno(idx, val)}
              cambiarNumero={(idx, val) => this.props.cambiarNumero(idx, val)}
            />
          </Col>
          <Col xs={2}>
            <Arista origen={22} destino={28} game={this.props.game}
              cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
            />
            <Tile idx={8} game={this.props.game}
              cambiarTerreno={(idx, val) => this.props.cambiarTerreno(idx, val)}
              cambiarNumero={(idx, val) => this.props.cambiarNumero(idx, val)}
            />
          </Col>
          <Col xs={2}>
            <Arista origen={23} destino={29} game={this.props.game}
              cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
            />
            <Tile idx={9} game={this.props.game}
              cambiarTerreno={(idx, val) => this.props.cambiarTerreno(idx, val)}
              cambiarNumero={(idx, val) => this.props.cambiarNumero(idx, val)}
            />
          </Col>
          <Col xs={2}>
            <Arista origen={24} destino={30} game={this.props.game}
              cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
            />
            <Tile idx={10} game={this.props.game}
              cambiarTerreno={(idx, val) => this.props.cambiarTerreno(idx, val)}
              cambiarNumero={(idx, val) => this.props.cambiarNumero(idx, val)}
            />
          </Col>
          <Col xs={2}>
            <Arista origen={25} destino={31} game={this.props.game}
              cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
            />
            <Tile idx={11} game={this.props.game}
              cambiarTerreno={(idx, val) => this.props.cambiarTerreno(idx, val)}
              cambiarNumero={(idx, val) => this.props.cambiarNumero(idx, val)}
            />
          </Col>
          <Col xs={1}>
            <Arista origen={26} destino={32} game={this.props.game}
              cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
            />
          </Col>
        </div>
        <div className="row">
          <Vertice idx={27} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={28} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={29} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={30} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={31} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={32} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
        </div>
        <div className="row">
          <div className="col-xs-1"/>
          <Arista origen={27} destino={33} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={28} destino={33} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={28} destino={34} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={29} destino={34} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={29} destino={35} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={30} destino={35} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={30} destino={36} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={31} destino={36} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={31} destino={37} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={32} destino={37} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
        </div>
        <div className="row">
          <div className="col-xs-1"/>
          <Vertice idx={33} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={34} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={35} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={36} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={37} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
        </div>
        <div className="row">
          <div className="col-xs-2"/>
          <Col xs={2}>
            <Arista origen={33} destino={38} game={this.props.game}
              cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
            />
            <Tile idx={12} game={this.props.game}
              cambiarTerreno={(idx, val) => this.props.cambiarTerreno(idx, val)}
              cambiarNumero={(idx, val) => this.props.cambiarNumero(idx, val)}
            />
          </Col>
          <Col xs={2}>
            <Arista origen={34} destino={39} game={this.props.game}
              cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
            />
            <Tile idx={13} game={this.props.game}
              cambiarTerreno={(idx, val) => this.props.cambiarTerreno(idx, val)}
              cambiarNumero={(idx, val) => this.props.cambiarNumero(idx, val)}
            />
          </Col>
          <Col xs={2}>
            <Arista origen={35} destino={40} game={this.props.game}
              cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
            />
            <Tile idx={14} game={this.props.game}
              cambiarTerreno={(idx, val) => this.props.cambiarTerreno(idx, val)}
              cambiarNumero={(idx, val) => this.props.cambiarNumero(idx, val)}
            />
          </Col>
          <Col xs={2}>
            <Arista origen={36} destino={41} game={this.props.game}
              cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
            />
            <Tile idx={15} game={this.props.game}
              cambiarTerreno={(idx, val) => this.props.cambiarTerreno(idx, val)}
              cambiarNumero={(idx, val) => this.props.cambiarNumero(idx, val)}
            />
          </Col>
          <Col xs={2}>
            <Arista origen={37} destino={42} game={this.props.game}
              cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
            />
          </Col>
        </div>
        <div className="row">
          <div className="col-xs-1"/>
          <Vertice idx={38} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={39} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={40} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={41} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={42} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
        </div>
        <div className="row">
          <div className="col-xs-2"/>
          <Arista origen={38} destino={43} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={39} destino={43} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={39} destino={44} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={40} destino={44} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={40} destino={45} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={41} destino={45} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={41} destino={46} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={42} destino={46} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
        </div>
        <div className="row">
          <div className="col-xs-2"/>
          <Vertice idx={43} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={44} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={45} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={46} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
        </div>
        <div className="row">
          <div className="col-xs-3"/>
          <Col xs={2}>
            <Arista origen={43} destino={47} game={this.props.game}
              cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
            />
            <Tile idx={16} game={this.props.game}
              cambiarTerreno={(idx, val) => this.props.cambiarTerreno(idx, val)}
              cambiarNumero={(idx, val) => this.props.cambiarNumero(idx, val)}
            />
          </Col>
          <Col xs={2}>
            <Arista origen={44} destino={48} game={this.props.game}
              cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
            />
            <Tile idx={17} game={this.props.game}
              cambiarTerreno={(idx, val) => this.props.cambiarTerreno(idx, val)}
              cambiarNumero={(idx, val) => this.props.cambiarNumero(idx, val)}
            />
          </Col>
          <Col xs={2}>
            <Arista origen={45} destino={49} game={this.props.game}
              cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
            />
            <Tile idx={18} game={this.props.game}
              cambiarTerreno={(idx, val) => this.props.cambiarTerreno(idx, val)}
              cambiarNumero={(idx, val) => this.props.cambiarNumero(idx, val)}
            />
          </Col>
          <Col xs={2}>
            <Arista origen={46} destino={50} game={this.props.game}
              cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
            />
          </Col>
        </div>
        <div className="row">
          <div className="col-xs-2"/>
          <Vertice idx={47} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={48} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={49} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={50} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
        </div>
        <div className="row">
          <div className="col-xs-3"/>
          <Arista origen={47} destino={51} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={48} destino={51} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={48} destino={52} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={49} destino={52} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={49} destino={53} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
          <Arista origen={50} destino={53} game={this.props.game}
            cambiarArista={(origen, destino) => this.props.cambiarArista(origen, destino)}
          />
        </div>
        <div className="row">
          <div className="col-xs-3"/>
          <Vertice idx={51} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={52} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
          <Vertice idx={53} game={this.props.game}
            cambiarVertice={(idx, val) => this.props.cambiarVertice(idx, val)}
          />
        </div>
      </div>
    );
  }
}