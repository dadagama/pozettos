<?php 
/*
 This file is part of Pozettos.

    Pozettos is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Pozettos is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Pozettos.  If not, see <http://www.gnu.org/licenses/>.

*/


require_once("../conexiones/ConexionBDMySQL.inc");
require_once("../herramientas/GeneradorHtml2.inc");

class Cliente
{
  var $_conexionBD; 
  var $_conexionBDAux;
  var $_html;
  
  function __construct($parametrosConexion)
  {
    $this->_conexionBD = new ConexionBDMySQL($parametrosConexion);
    $this->_conexionBD->conectar();
    $this->_conexionBDAux = new ConexionBDMySQL($parametrosConexion);
    $this->_conexionBDAux->conectar();
    $this->_html = new GeneradorHtml2();
  }
  
  function actualizarListaClientes()
  {
    $sql = "SELECT temp.*, TIME_FORMAT(SEC_TO_TIME((segundos_acumulados/5) - if(segundos_gratis_cobrados,segundos_gratis_cobrados,0)), '%H:%i') AS cli_horas_gratis_disponibles
                    , TIME_FORMAT(SEC_TO_TIME(segundos_acumulados - (if(segundos_gratis_cobrados,segundos_gratis_cobrados,0)*5)), '%H:%i') AS cli_tiempo_acumulado
                    , SEC_TO_TIME(segundos_acumulados) as sg_acumulados
                    , SEC_TO_TIME(segundos_gratis_cobrados) as sg_gratis_cobrados
            FROM (SELECT cli_id, cli_nombre, cli_apellido, cli_email,
                        ( SELECT SUM(TIME_TO_SEC(hiv_dus_minutos))
                          FROM pozettos_historico_venta
                          WHERE cli_id = hiv_cli_id
                                AND hiv_pago = 1
                                AND hiv_es_tiempo_gratis = 0
                                AND hiv_vigente = 1) AS segundos_acumulados,
                        ( SELECT SUM(TIME_TO_SEC(hiv_dus_minutos))
                          FROM pozettos_historico_venta
                          WHERE cli_id = hiv_cli_id
                                AND hiv_pago = 0
                                AND hiv_es_tiempo_gratis = 1
                                AND hiv_vigente = 1) AS segundos_gratis_cobrados
                  FROM pozettos_cliente) AS temp";
    $this->_conexionBD->ejecutarSQL($sql);
    $filas_clientes = "";              
    while($info_cliente = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
    {
      $lbl_id = $this->_html->tag("label", "", array($info_cliente['cli_id']));
      $cli_id = $this->_html->tag("td", "class='alineacion_centro letra_9 verdana'", array($lbl_id));
      $lbl_nombre = $this->_html->tag("label", "class='cursor_cruz'", array(utf8_encode($info_cliente['cli_nombre'])));
      $cli_nombre = $this->_html->tag("td", "id='cli_nombre_".$info_cliente['cli_id']."' class='alineacion_izquierda letra_9 verdana cursor_cruz' onclick='editarCampo(\"cli_nombre_".$info_cliente['cli_id']."\",true);'", array($lbl_nombre));
      $lbl_apellido = $this->_html->tag("label", "class='cursor_cruz'", array(utf8_encode($info_cliente['cli_apellido'])));
      $cli_apellido = $this->_html->tag("td", "id='cli_apellido_".$info_cliente['cli_id']."' class='alineacion_izquierda letra_9 verdana cursor_cruz' onclick='editarCampo(\"cli_apellido_".$info_cliente['cli_id']."\",true);'", array($lbl_apellido));
      $lbl_email = $this->_html->tag("label", "class='cursor_cruz'", array(utf8_encode($info_cliente['cli_email'])));
      $cli_email = $this->_html->tag("td", "id='cli_email_".$info_cliente['cli_id']."' class='alineacion_izquierda letra_9 verdana cursor_cruz' onclick='editarCampo(\"cli_email_".$info_cliente['cli_id']."\",true);'", array($lbl_email));
      $letra_roja = "";
      if(substr($info_cliente['cli_horas_gratis_disponibles'],0,1) == "-")
        $letra_roja = "letra_roja";
      $cli_tiempo_acumulado = $this->_html->tag("td", "class='alineacion_centro letra_9 verdana $letra_roja'", array($info_cliente['cli_tiempo_acumulado']));
      $cli_horas_gratis_disponibles = $this->_html->tag("td", "class='alineacion_centro letra_9 verdana $letra_roja'", array($info_cliente['cli_horas_gratis_disponibles']));
      //para depuracion
//       $time_acumulado = $this->_html->tag("td", "class='alineacion_centro letra_9 verdana'", array($info_cliente['segundos_acumulados']));
//       $sg_acumulados = $this->_html->tag("td", "class='alineacion_centro letra_9 verdana'", array($info_cliente['sg_acumulados']));
//       $time_gratis_cobrados = $this->_html->tag("td", "class='alineacion_centro letra_9 verdana'", array($info_cliente['segundos_gratis_cobrados']));
//       $sg_gratis_cobrados = $this->_html->tag("td", "class='alineacion_centro letra_9 verdana'", array($info_cliente['sg_gratis_cobrados']));
      
      $tr_cliente = $this->_html->tag("tr", "", array($cli_id,$cli_nombre,$cli_apellido,$cli_email,$cli_tiempo_acumulado,$cli_horas_gratis_disponibles,
                                                      $time_acumulado,$sg_acumulados,$time_gratis_cobrados,$sg_gratis_cobrados));
      $filas_clientes .= $tr_cliente;
    }
    return $filas_clientes;
  }
  
  function agregarCliente($cli_nombre, $cli_apellido, $cli_email)
  {
    $sql = "INSERT INTO pozettos_cliente(cli_nombre, cli_apellido, cli_email)
            VALUES('".utf8_decode($cli_nombre)."', '".utf8_decode($cli_apellido)."', '".utf8_decode($cli_email)."')";
    $this->_conexionBD->ejecutarSQL($sql);
    if ($this->_conexionBD->obtenerNumeroFilasAfectadas())
    {
      $sql = "SELECT cli_id, cli_nombre, cli_apellido, cli_email
              FROM pozettos_cliente
              WHERE cli_vigente = 1
              ORDER BY cli_id DESC LIMIT 1";
      $this->_conexionBD->ejecutarSQL($sql);
      $info_cliente = $this->_conexionBD->obtenerFilaComoArregloAsociativo();
      $cli_id = $this->_html->tag("td", "class='alineacion_centro letra_9 verdana'", array($info_cliente['cli_id']));
      $cli_nombre = $this->_html->tag("td", "id='cli_nombre_".$info_cliente['cli_id']."' class='alineacion_izquierda letra_9 verdana cursor_cruz' onclick='editarCampo(\"cli_nombre_".$info_cliente['cli_id']."\",true);'", array(utf8_encode($info_cliente['cli_nombre'])));
      $cli_apellido = $this->_html->tag("td", "id='cli_apellido_".$info_cliente['cli_id']."' class='alineacion_izquierda letra_9 verdana cursor_cruz' onclick='editarCampo(\"cli_apellido_".$info_cliente['cli_id']."\",true);'", array(utf8_encode($info_cliente['cli_apellido'])));
      $cli_email = $this->_html->tag("td", "id='cli_email_".$info_cliente['cli_id']."' class='alineacion_izquierda letra_9 verdana cursor_cruz' onclick='editarCampo(\"cli_email_".$info_cliente['cli_id']."\",true);'", array(utf8_encode($info_cliente['cli_email'])));
      $cli_horas_gratis = $this->_html->tag("td", "class='alineacion_centro letra_9 verdana'", array("0"));
      $tr_cliente = $this->_html->tag("tr", "", array($cli_id,$cli_nombre,$cli_apellido,$cli_email,$cli_horas_gratis));
      return $tr_cliente;
    }
    else
      return false;
  }
  
  function actualizarValor($cli_id,$valor_nuevo,$nombre_campo)
  {
    if(!$valor_nuevo)
      $valor_nuevo = "";
    $sql = "UPDATE pozettos_cliente
            SET $nombre_campo = '".utf8_decode($valor_nuevo)."'
            WHERE cli_id = '$cli_id'";
    //echo $sql;
    $this->_conexionBD->ejecutarSQL($sql);
    if ($this->_conexionBD->obtenerNumeroFilasAfectadas())
      return true;
    else
      return false;
  }
}
?>