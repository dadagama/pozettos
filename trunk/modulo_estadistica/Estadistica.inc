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
require_once("../herramientas/GeneradorHtml.inc");

class Estadistica
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
    $this->_html = new GeneradorHtml();
  }
  
  function cargarCategorias()
  {
    $sql = "SELECT cat_id, cat_nombre 
            FROM pozettos_categoria
            WHERE cat_id != 1";
    $this->_conexionBD->ejecutarSQL($sql);
    $contador = 0;
    $this->_html->tag("table");
      $this->_html->tag("tr");          
        while($info_categoria = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
        {
          if($contador % 1 == 0)
          {
            $this->_html->end("tr");
            $this->_html->tag("tr");  
          }
          $this->_html->tag("td");
            $this->_html->tag("label", array("class"=>"letra_azul verdana letra_9 negrilla"));
              $this->_html->tag("input", array("type"=>"checkbox", "name"=>$info_categoria['cat_nombre'], "id"=>"chk_".$info_categoria['cat_id'], "checked"=>"checked"),true);
              $this->_html->printText(utf8_encode($info_categoria['cat_nombre']));
            $this->_html->end("label");
          $this->_html->end("td");
          $contador++;
        }
      $this->_html->end("tr");
    $this->_html->end("table");
  }
  
  function actualizarEstadisticas(&$arreglo_parametros)
  {
    switch($arreglo_parametros['opc_alcance'])
    {
      case "diario":
        $fecha = "hiv_fecha = '".$arreglo_parametros['opc_fecha']."'";
        break;
        
      case "mensual":
        $fecha = "hiv_fecha LIKE '".$arreglo_parametros['opc_anno']."-".$arreglo_parametros['opc_mes']."-__'";
        break;
        
      case "rango":
         $fecha = "hiv_fecha >= '".$arreglo_parametros['opc_fecha_inicial']."' AND hiv_fecha <= '".$arreglo_parametros['opc_fecha_final']."'";
        break;
    }
    $this->_html->tag("tr");
      $this->_html->tag("td");
        $this->_html->tag("table", array("class"=>"tbl_resumen"));
          if($arreglo_parametros['Cabinas'])
            $this->_construirTablaResumen($fecha, "Cabinas");
          if($arreglo_parametros['Juegos'])
            $this->_construirTablaResumen($fecha, "Juegos");
          if($arreglo_parametros['Recargas'])
            if($arreglo_parametros['opc_alcance'] == "diario")
              $this->_construirTablaResumen($fecha, "Recargas", true, $arreglo_parametros['opc_fecha']);
            else
              $this->_construirTablaResumen($fecha, "Recargas");
          if($arreglo_parametros['Llamadas'])
            $this->_construirTablaResumen($fecha, "Llamadas");
          if($arreglo_parametros['Otros'])
            $this->_construirTablaResumen($fecha, "Otros");
        $this->_html->end("table");
      $this->_html->end("td");
    $this->_html->end("tr");
  }
  
  function _construirTablaResumen($where_fecha, $cat_nombre, $mostrar_saldo_titan = false, $fecha = "")
  {
    $sql = "SELECT ser_nombre, ser_id
            FROM pozettos_servicio, pozettos_categoria, pozettos_categoria_servicios
            WHERE cas_ser_id = ser_id
            AND cas_cat_id = cat_id
            AND cat_nombre = '$cat_nombre'
            ORDER BY ser_nombre ASC";
    $this->_conexionBD->ejecutarSQL($sql);
    
    $this->_html->tag("thead");
      $this->_html->tag("tr");          
        $this->_html->tag("th", array("class"=>"ancho_140"));
          $this->_html->tag("label");
            $this->_html->printText($cat_nombre);
          $this->_html->end("label");
        $this->_html->end("th");
        
        $this->_html->tag("th", array("class"=>"ancho_70"));
          $this->_html->tag("label");
            $this->_html->printText("Pagado");
          $this->_html->end("label");
        $this->_html->end("th");
        
        $this->_html->tag("th", array("class"=>"ancho_70"));
          $this->_html->tag("label");
            $this->_html->printText("Deben");
          $this->_html->end("label");
        $this->_html->end("th");
        
        $this->_html->tag("th", array("class"=>"ancho_70"));
          $this->_html->tag("label");
            $this->_html->printText("Gratis");
          $this->_html->end("label");
        $this->_html->end("th");
      $this->_html->end("tr");
    $this->_html->end("thead");
      
    $total_pagado = 0;
    $total_deben = 0;
    $total_gratis = 0;
      
    $this->_html->tag("tbody");
      while($info_cabina = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
      {     
        $this->_html->tag("tr");
          $this->_html->tag("td", array("class"=>"alineacion_izquierda"));
            $this->_html->tag("label");
              $this->_html->printText($info_cabina['ser_nombre']);
            $this->_html->end("label");
          $this->_html->end("td");
          
          $this->_html->tag("td", array("class"=>"alineacion_derecha"));
            $this->_html->tag("label");
              $sql = "SELECT SUM(hiv_total)
                      FROM pozettos_historico_venta
                      WHERE hiv_ser_id = '".$info_cabina['ser_id']."'
                      AND hiv_pago = 1
                      AND hiv_es_tiempo_gratis = 0
                      AND $where_fecha";
              $this->_conexionBDAux->ejecutarSQL($sql);
              $total = $this->_conexionBDAux->obtenerFilaComoCadena();
              $total_pagado += (int)$total;
              $this->_html->printText($this->_html->colocarPuntoMiles($total));
            $this->_html->end("label");
          $this->_html->end("td");
          
          $this->_html->tag("td", array("class"=>"alineacion_derecha"));
            $this->_html->tag("label");
              $sql = "SELECT SUM(hiv_total)
                      FROM pozettos_historico_venta
                      WHERE hiv_ser_id = '".$info_cabina['ser_id']."'
                      AND hiv_pago = 0
                      AND hiv_es_tiempo_gratis = 0
                      AND $where_fecha";
              $this->_conexionBDAux->ejecutarSQL($sql);
              $total = $this->_conexionBDAux->obtenerFilaComoCadena();
              $total_deben += (int)$total;
              $this->_html->printText($this->_html->colocarPuntoMiles($total));
            $this->_html->end("label");
          $this->_html->end("td");
          
          $this->_html->tag("td", array("class"=>"alineacion_derecha"));
            $this->_html->tag("label");
              $sql = "SELECT SUM(hiv_total)
                      FROM pozettos_historico_venta
                      WHERE hiv_ser_id = '".$info_cabina['ser_id']."'
                      AND hiv_pago = 0
                      AND hiv_es_tiempo_gratis = 1
                      AND $where_fecha";
              $this->_conexionBDAux->ejecutarSQL($sql);
              $total = $this->_conexionBDAux->obtenerFilaComoCadena();
              $total_gratis += (int)$total;
              $this->_html->printText($this->_html->colocarPuntoMiles($total));
            $this->_html->end("label");
          $this->_html->end("td");
        $this->_html->end("tr");
      }
      
      $this->_html->tag("tr");
        $this->_html->tag("td", array("class"=>"celda_subtotal"));
          $this->_html->tag("label");
            $this->_html->printText("Subtotal");
          $this->_html->end("label");
        $this->_html->end("td");
        
        $this->_html->tag("td", array("class"=>"celda_subtotal alineacion_derecha"));
          $this->_html->tag("label");
            $this->_html->printText($this->_html->colocarPuntoMiles($total_pagado));
          $this->_html->end("label");
        $this->_html->end("td");
        
        $this->_html->tag("td", array("class"=>"celda_subtotal alineacion_derecha"));
          $this->_html->tag("label");
            $this->_html->printText($this->_html->colocarPuntoMiles($total_deben));
          $this->_html->end("label");
        $this->_html->end("td");
        
        $this->_html->tag("td", array("class"=>"celda_subtotal alineacion_derecha"));
          $this->_html->tag("label");
            $this->_html->printText($this->_html->colocarPuntoMiles($total_gratis));
          $this->_html->end("label");
        $this->_html->end("td");
      $this->_html->end("tr");
      
      $this->_html->tag("tr");
        $this->_html->tag("td", array("class"=>"celda_total"));
          $this->_html->tag("label");
            $this->_html->printText("Total $cat_nombre");
          $this->_html->end("label");
        $this->_html->end("td");
        
        $this->_html->tag("td", array("class"=>"celda_total alineacion_centro", "colspan"=>"2"));
          $this->_html->tag("label");
            $this->_html->printText($this->_html->colocarPuntoMiles($total_pagado + $total_deben));
          $this->_html->end("label");
        $this->_html->end("td");
        
//         $this->_html->tag("td", array("class"=>"celda_total"));
//         $this->_html->end("td");
      $this->_html->end("tr");
      
      if($mostrar_saldo_titan)
      {
        $this->_html->tag("tr");
          $this->_html->tag("td", array("class"=>"celda_total_2"));
            $this->_html->tag("label");
              $this->_html->printText("Saldo Inicial Titan");
            $this->_html->end("label");
          $this->_html->end("td");
             
          $this->_html->tag("td", array("class"=>"celda_total_2 alineacion_centro", "colspan"=>"3"));
            $this->_html->tag("label");
              $sql = "SELECT sit_saldo
                      FROM pozettos_saldo_inicial_titan
                      WHERE sit_fecha = '$fecha' LIMIT 1";
              $this->_conexionBDAux->ejecutarSQL($sql);
              if($this->_conexionBDAux->obtenerNumeroFilas() > 0)
              {
                $total = $this->_conexionBDAux->obtenerFilaComoCadena();
                $this->_html->printText($this->_html->colocarPuntoMiles($total));
              }
              else
                $this->_html->printText("0");
            $this->_html->end("label");
          $this->_html->end("td");
        $this->_html->end("tr");
              
        $this->_html->tag("tr");          
          $this->_html->tag("td", array("class"=>"celda_total_2"));
            $this->_html->tag("label");
              $this->_html->printText("Saldo Final Titan");
            $this->_html->end("label");
          $this->_html->end("td");
             
          $this->_html->tag("td", array("class"=>"celda_total_2 alineacion_centro", "colspan"=>"3"));
            $this->_html->tag("label");
              $this->_html->printText($this->_html->colocarPuntoMiles($total - $total_pagado - $total_deben - $total_gratis));
            $this->_html->end("label");
          $this->_html->end("td");
        $this->_html->end("tr");
      }
    $this->_html->end("tbody");
  }
}
?>