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

class Estadistica
{
  var $_conexionBD; 
  var $_conexionBDAux;
  var $_html;
  var $_resumen_general;
  var $_total_general;
  
  function __construct($parametrosConexion)
  {
    $this->_conexionBD = new ConexionBDMySQL($parametrosConexion);
    $this->_conexionBD->conectar();
    $this->_conexionBDAux = new ConexionBDMySQL($parametrosConexion);
    $this->_conexionBDAux->conectar();
    $this->_html = new GeneradorHtml2();
    $this->_resumen_general = array();
    $this->_total_general = 0;
  }
  
  function cargarCategorias()
  {
    $sql = "SELECT cat_id, cat_nombre
            FROM pozettos_categoria
            WHERE cat_id != 1
            AND cat_vigente = 1";
    $this->_conexionBD->ejecutarSQL($sql);
    $arreglo_tr_categorias = "";
    while($info_categoria = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
    {
            $input_categoria = $this->_html->tag("input", "type='checkbox' name='".$info_categoria['cat_nombre']."' id='chk_".$info_categoria['cat_id']."' checked='checked'", "", true);
          $label_categoria = $this->_html->tag("label", "class='letra_azul verdana letra_9'", array($input_categoria,utf8_encode($info_categoria['cat_nombre'])));
        $td_categoria = $this->_html->tag("td", "", array($label_categoria));
      $tr_categorias .= $this->_html->tag("tr", "", array($td_categoria));
      $contador++;
    }
    return $this->_html->tag("table", "", array($tr_categorias));
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
      $tablas_resumenes = "";  
      if($arreglo_parametros['Cabinas'])
        $tablas_resumenes .= $this->_construirTablaResumen($fecha, "Cabinas");
      if($arreglo_parametros['Juegos'])
        $tablas_resumenes .= $this->_construirTablaResumen($fecha, "Juegos");
      if($arreglo_parametros['Recargas'])
        if($arreglo_parametros['opc_alcance'] == "diario")
          $tablas_resumenes .= $this->_construirTablaResumen($fecha, "Recargas", true, $arreglo_parametros['opc_fecha']);
        else
          $tablas_resumenes .= $this->_construirTablaResumen($fecha, "Recargas");
      if($arreglo_parametros['Llamadas'])
        $tablas_resumenes .= $this->_construirTablaResumen($fecha, "Llamadas");
      if($arreglo_parametros['Otros'])
        $tablas_resumenes .= $this->_construirTablaResumen($fecha, "Otros");
      $tablas_resumenes = $this->_construirTablaResumenGeneral()."".$tablas_resumenes;
      $tabla_resumen = $this->_html->tag("table", "class='tbl_resumen'", array($tablas_resumenes));
    $td_estadisticas = $this->_html->tag("td", "", array($tabla_resumen));
    return $this->_html->tag("tr", "", array($td_estadisticas));
  }
  
  function _construirTablaResumenGeneral()
  {
        $th_categoria = $this->_html->tag("th", "class='ancho_140'", array("<label>Nombre Categoria</label>"));
        $th_total = $this->_html->tag("th", "class='ancho_70'", array("<label>Total por Categoría</label>"));
      $tr_encabezado = $this->_html->tag("tr", "", array($th_categoria,$th_total));
    $thead_resumen = $this->_html->tag("thead", "", array($tr_encabezado));
    
    $totales = "";
    foreach ($this->_resumen_general  AS $fila)
      $totales .= $this->_html->tag("tr", "", array($fila));
      
      $td_total = $this->_html->tag("td", "class='celda_total'", array("<label>Total</label>"));
      $td_total_entrada = $this->_html->tag("td", "class='celda_total alineacion_derecha' colspan='1'", array("<label>".$this->_html->colocarPuntoMiles($this->_total_general)."</label>"));
    $tr_total = $this->_html->tag("tr", "", array($td_total,$td_total_entrada));
    $totales .= $tr_total;
    $tbody_resumen = $this->_html->tag("tbody", "", array($totales));
    
    return $thead_resumen." ".$tbody_resumen;
  }
  
  function _construirTablaResumen($where_fecha, $cat_nombre, $mostrar_saldo_titan = false, $fecha = "")
  {
    $sql = "SELECT ser_nombre, ser_id
            FROM pozettos_servicio, pozettos_categoria, pozettos_categoria_servicios
            WHERE cas_ser_id = ser_id
            AND cas_cat_id = cat_id
            AND cat_nombre = '$cat_nombre'
            AND cat_vigente = 1
						AND cas_vigente = 1
						AND ser_vigente = 1
            ORDER BY ser_nombre ASC";
    $this->_conexionBD->ejecutarSQL($sql);
    
        $th_nombre_categoria = $this->_html->tag("th", "class='ancho_140'", array("<label>$cat_nombre</label>"));
        $th_pagado = $this->_html->tag("th", "class='ancho_70'", array("<label>Pagado</label>"));
        $th_deben = $this->_html->tag("th", "class='ancho_70'", array("<label>Deben</label>"));
        $th_gratis = $this->_html->tag("th", "class='ancho_70'", array("<label>Gratis</label>"));
      $tr_encabezado = $this->_html->tag("tr", "", array($th_nombre_categoria,$th_pagado,$th_deben,$th_gratis));
    $thead_resumen = $this->_html->tag("thead", "", array($tr_encabezado));

    $total_pagado = 0;
    $total_deben = 0;
    $total_gratis = 0;
      
    $trs_servicios = "";
    while($info_cabina = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
    {
        $td_nombre_servicio = $this->_html->tag("td", "class='alineacion_izquierda'", array("<label>".$info_cabina['ser_nombre']."</label>"));
        $sql = "SELECT SUM(hiv_total)
                FROM pozettos_historico_venta
                WHERE hiv_ser_id = '".$info_cabina['ser_id']."'
                      AND hiv_pago = 1
                      AND hiv_es_tiempo_gratis = 0
                      AND hiv_vigente = 1
                      AND $where_fecha";
        $this->_conexionBDAux->ejecutarSQL($sql);
        $total = (int)$this->_conexionBDAux->obtenerFilaComoCadena();
        $total_pagado += $total;
        $td_pago = $this->_html->tag("td", "class='alineacion_derecha'", array("<label>".$this->_html->colocarPuntoMiles($total)."</label>"));

        $sql = "SELECT SUM(hiv_total)
                FROM pozettos_historico_venta
                WHERE hiv_ser_id = '".$info_cabina['ser_id']."'
                      AND hiv_pago = 0
                      AND hiv_es_tiempo_gratis = 0
                      AND hiv_vigente = 1
                      AND $where_fecha";
        $this->_conexionBDAux->ejecutarSQL($sql);
        $total = (int)$this->_conexionBDAux->obtenerFilaComoCadena();
        $total_deben += $total;
        $td_deben = $this->_html->tag("td", "class='alineacion_derecha'", array("<label>".$this->_html->colocarPuntoMiles($total)."</label>"));

        $sql = "SELECT SUM(hiv_total)
                FROM pozettos_historico_venta
                WHERE hiv_ser_id = '".$info_cabina['ser_id']."'
                      AND hiv_pago = 0
                      AND hiv_es_tiempo_gratis = 1
                      AND hiv_vigente = 1
                      AND $where_fecha";
        $this->_conexionBDAux->ejecutarSQL($sql);
        $total = (int)$this->_conexionBDAux->obtenerFilaComoCadena();
        $total_gratis += $total;
        $td_gratis = $this->_html->tag("td", "class='alineacion_derecha'", array("<label>".$this->_html->colocarPuntoMiles($total)."</label>"));

      $trs_servicios .= $this->_html->tag("tr", "", array($td_nombre_servicio,$td_pago,$td_deben,$td_gratis));
    }
    //subtotales
      $td_subtotal = $this->_html->tag("td", "class='celda_subtotal'", array("<label>Subtotal</label>"));
      $td_total_pagado = $this->_html->tag("td", "class='celda_subtotal alineacion_derecha'", array("<label>".$this->_html->colocarPuntoMiles($total_pagado)."</label>"));
      $td_total_deben = $this->_html->tag("td", "class='celda_subtotal alineacion_derecha'", array("<label>".$this->_html->colocarPuntoMiles($total_deben)."</label>"));
      $td_total_gratis = $this->_html->tag("td", "class='celda_subtotal alineacion_derecha'", array("<label>".$this->_html->colocarPuntoMiles($total_gratis)."</label>"));
    $tr_subtotal = $this->_html->tag("tr", "", array($td_subtotal,$td_total_pagado,$td_total_deben,$td_total_gratis));
    //totales
      $td_total = $this->_html->tag("td", "class='celda_total'", array("<label>Total $cat_nombre</label>"));
      $td_total_entrada = $this->_html->tag("td", "class='celda_total alineacion_centro' colspan='2'", array("<label>".$this->_html->colocarPuntoMiles($total_pagado + $total_deben)."</label>"));
    $tr_total = $this->_html->tag("tr", "", array($td_total,$td_total_entrada));

    //añado totales al arreglo de resumen general
    $td_label_total_general = $this->_html->tag("td", "class='celda_subtotal'", array("<label>$cat_nombre</label>"));
    $td_total_general = $this->_html->tag("td", "class='celda_subtotal alineacion_derecha' colspan='1'", array("<label>".$this->_html->colocarPuntoMiles($total_pagado + $total_deben)."</label>"));
    $this->_resumen_general[] = $td_label_total_general."".$td_total_general;
    $this->_total_general += ($total_pagado + $total_deben); 
    
    $trs_titan = "";
    if($mostrar_saldo_titan)
    {
        $td_label_titan = $this->_html->tag("td", "class='celda_total_2'", array("<label>Saldo Inicial Titan</label>"));
        $sql = "SELECT sit_saldo
                FROM pozettos_saldo_inicial_titan
                WHERE sit_fecha = '$fecha'
                AND sit_vigente = 1
                LIMIT 1";
        $this->_conexionBDAux->ejecutarSQL($sql);
        if($this->_conexionBDAux->obtenerNumeroFilas() > 0)
          $total = $this->_conexionBDAux->obtenerFilaComoCadena();
        else
          $total = "0";
        $td_saldo_titan = $this->_html->tag("td", "class='celda_total_2 alineacion_centro' colspan='3'", array("<label>".$this->_html->colocarPuntoMiles($total)."</label>"));
      $tr_total_titan = $this->_html->tag("tr", "", array($td_label_titan,$td_saldo_titan));

      $td_label_saldo_final = $this->_html->tag("td", "class='celda_total_2'", array("<label>Saldo Final Titan</label>"));
      $td_saldo_final = $this->_html->tag("td", "class='celda_total_2 alineacion_centro' colspan='3'", array("<label>".$this->_html->colocarPuntoMiles($total - $total_pagado - $total_deben - $total_gratis)."</label>"));
      $tr_saldo_final = $this->_html->tag("tr", "", array($td_label_saldo_final,$td_saldo_final));

      $trs_titan = $tr_total_titan." ".$tr_saldo_final;
    }
    $tbody_resumen = $this->_html->tag("tbody", "", array($trs_servicios,$tr_subtotal,$tr_total,$trs_titan));
    return $thead_resumen." ".$tbody_resumen;
  }
}
?>