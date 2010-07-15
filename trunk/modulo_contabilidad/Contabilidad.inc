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

class Contabilidad
{
  var $_conexionBD; 
  var $_conexionBDAux;
  var $_html;
  var $_fecha_contabilidad;
  
  function __construct($parametrosConexion, $fecha_contabilidad)
  {
    $this->_conexionBD = new ConexionBDMySQL($parametrosConexion);
    $this->_conexionBD->conectar();
    $this->_conexionBDAux = new ConexionBDMySQL($parametrosConexion);
    $this->_conexionBDAux->conectar();
    $this->_html = new GeneradorHtml2();
    $this->_fecha_contabilidad = $fecha_contabilidad;
  }

/**********************************
******* ACCIONES GENERICAS  *******
***********************************/

  function obtenerTablaServicios()
  {
    //tr servicios
//     $select_duracion = $this->_html->select($this->_conexionBDAux, "dus_minutos", "dus_texto", "pozettos_duracion_servicio", "", "00:00:00", "id='hiv_dus_minutos' class='ancho_80 verdana letra_9 alineacion_centro letra_roja negrilla' title='Duracion del servicio'");
//     $arreglo_servicios[] = $this->_html->tag("td", "", array($select_duracion));
    $sql = "SELECT ser_nombre,ser_url_foto,ser_onclick
            FROM pozettos_servicio
            WHERE ser_tipo='servicio'
            AND ser_vigente = 1
            ORDER BY ser_id ASC";
    $this->_conexionBD->ejecutarSQL($sql);
    $contador = 1;
    while($info_servicio = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
    {
      // if($contador % 10 == 0)
      // {
        // $this->_html->end("tr");
        // $this->_html->tag("tr");
          // $this->_html->tag("td");
          // $this->_html->end("td");
      // }
      $img_servicio = $this->_html->tag("img", "src='".$info_servicio['ser_url_foto']."'");
      $button_servicio = $this->_html->tag("button", "onclick=\"".$info_servicio['ser_onclick']."\" title='".$info_servicio['ser_nombre']."'", array($img_servicio));
      $arreglo_servicios[] = $this->_html->tag("td","",array($button_servicio));
      $contador++;
    }
    $tr_servicios = $this->_html->tag("tr", "", $arreglo_servicios);
    
    //tr productos
//     $input_total = $this->_html->tag("input", "id='hiv_total' class='ancho_80 alineacion_centro letra_roja verdana negrilla' title='Total a pagar' type='text'","",true);
//     $arreglo_productos[] = $this->_html->tag("td", "", array($input_total));
    $sql = "SELECT ser_nombre,ser_url_foto,ser_onclick
            FROM pozettos_servicio
            WHERE ser_tipo='producto'
            ORDER BY ser_id ASC";
    $this->_conexionBD->ejecutarSQL($sql);
    $contador = 1;
    while($info_producto = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
    {
      // if($contador % 10 == 0)
      // {
        // $this->_html->end("tr");
        // $this->_html->tag("tr");
          // $this->_html->tag("td");
          // $this->_html->end("td");
      // }
      $img_producto = $this->_html->tag("img", "src='".$info_producto['ser_url_foto']."'");
      $button_producto = $this->_html->tag("button", "onclick=\"".$info_producto['ser_onclick']."\" title='".$info_producto['ser_nombre']."'", array($img_producto));
      $arreglo_productos[] = $this->_html->tag("td","",array($button_producto));
      $contador++;
    }
    $tr_productos = $this->_html->tag("tr", "", $arreglo_productos);
    
    return $this->_html->tag("table", "id='tbl_servicios'", array($tr_servicios,$tr_productos));
  }
  
  function cargarSaldoInicialTitan($sit_fecha)
  {
    $sql = "SELECT sit_saldo
            FROM pozettos_saldo_inicial_titan
            WHERE sit_fecha='$sit_fecha'
             AND sit_vigente = 1
            LIMIT 1";
    $this->_conexionBD->ejecutarSQL($sql);
    if($this->_conexionBD->obtenerNumeroFilas())
      return $this->_conexionBD->obtenerFilaComoCadena();
    else
    {
      $sql = "INSERT INTO pozettos_saldo_inicial_titan (sit_saldo, sit_fecha)
              VALUES ('0','$sit_fecha')";
      $this->_conexionBD->ejecutarSQL($sql);
      return "0";
    }
  }
  
  function actualizarSaldoTitan($sit_saldo, $sit_fecha)
  {
    if(!$sit_saldo)
      $sit_saldo = "0";
    $sql = "UPDATE pozettos_saldo_inicial_titan
            SET sit_saldo = '$sit_saldo'
            WHERE sit_fecha = '$sit_fecha'";
    //echo $sql;
    $this->_conexionBD->ejecutarSQL($sql);
    if ($this->_conexionBD->obtenerNumeroFilasAfectadas())
      return true;
    else
      return false;
  }
  
  function actualizarSaldoEgresos($egd_saldo, $egd_fecha)
  {
    if(!$egd_saldo)
      $egd_saldo = "0";
    $sql = "UPDATE pozettos_egreso_diario
            SET egd_saldo = '$egd_saldo'
            WHERE egd_fecha = '$egd_fecha'";
    //echo $sql;
    $this->_conexionBD->ejecutarSQL($sql);
    if ($this->_conexionBD->obtenerNumeroFilasAfectadas())
      return true;
    else
      return false;
  }
  
  function obtenerOptions()
  {
    $arreglo_options = array();
    /*  CLIENTES  */
    $sql = "SELECT cli_id,cli_nombre,cli_apellido
            FROM pozettos_cliente
            WHERE cli_vigente = 1
            ORDER BY cli_id DESC";
    $this->_conexionBD->ejecutarSQL($sql);
    $options_clientes = "";
    while($info_option = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
      $options_clientes .= $this->_html->tag( "option",
                                              "value='".$info_option['cli_id']."'",
                                              array($info_option['cli_id']."&nbsp;->&nbsp;".utf8_encode($info_option['cli_nombre'])." ".utf8_encode($info_option['cli_apellido']))
                                              );
    $arreglo_options['options_clientes'] = $options_clientes;
    
    /*  DURACION  */
    $sql = "SELECT dus_minutos,dus_texto
            FROM pozettos_duracion_servicio
            WHERE dus_vigente = 1
            ORDER BY dus_minutos ASC";
    $this->_conexionBD->ejecutarSQL($sql);
    $options_duracion = "";
    while($info_option = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
      $options_duracion .= $this->_html->tag( "option",
                                              "value='".$info_option['dus_minutos']."'",
                                              array($info_option['dus_texto'])
                                              );
    $arreglo_options['options_duracion'] = $options_duracion;
    
    /*  HORA  */
//     $sql = "SELECT dus_minutos,dus_texto
//             FROM pozettos_duracion_servicio
//             ORDER BY dus_minutos ASC";
//     $options_hora = "";
//     while($info_option = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
//       $options_hora .= $this->_html->tag( "option",
//                                           "value='".$info_option['dus_minutos']."'",
//                                           array($info_option['dus_texto']),
//                                           true);
//     $arreglo_options['options_duracion'] = $options_hora;
    
    /* SALDO TITAN */
    $sql = "SELECT sit_saldo
            FROM pozettos_saldo_inicial_titan
            WHERE sit_fecha='". $this->_fecha_contabilidad ."'
            AND sit_vigente = 1
            LIMIT 1";
    $this->_conexionBD->ejecutarSQL($sql);
    if($this->_conexionBD->obtenerNumeroFilas())
      $arreglo_options['sit_saldo'] = $this->_conexionBD->obtenerFilaComoCadena();
    else
    {
      $sql = "INSERT INTO pozettos_saldo_inicial_titan (sit_saldo, sit_fecha)
              VALUES ('0','". $this->_fecha_contabilidad ."')";
      $this->_conexionBD->ejecutarSQL($sql);
      $arreglo_options['sit_saldo'] = "0";
    }
    
    /* SALDO EGRESOS */
    $sql = "SELECT egd_saldo
            FROM pozettos_egreso_diario
            WHERE egd_fecha='". $this->_fecha_contabilidad ."'
            AND egd_vigente = 1
            LIMIT 1";
    $this->_conexionBD->ejecutarSQL($sql);
    if($this->_conexionBD->obtenerNumeroFilas())
      $arreglo_options['egd_saldo'] = $this->_conexionBD->obtenerFilaComoCadena();
    else
    {
      $sql = "INSERT INTO pozettos_egreso_diario (egd_saldo, egd_fecha)
              VALUES ('0','". $this->_fecha_contabilidad ."')";
      $this->_conexionBD->ejecutarSQL($sql);
      $arreglo_options['egd_saldo'] = "0";
    }
    return json_encode($arreglo_options);
  }

  function actualizarValor($hiv_id,$valor_nuevo,$nombre_campo)
  {
    if(!$valor_nuevo)
      $valor_nuevo = "";
    $sql = "UPDATE pozettos_historico_venta
            SET $nombre_campo = '".utf8_decode($valor_nuevo)."'
            WHERE hiv_id = '$hiv_id'";
    //echo $sql;
    $this->_conexionBD->ejecutarSQL($sql);
    if ($this->_conexionBD->obtenerNumeroFilasAfectadas())
      return true;
    else
      return false;
  }
  
  function actualizarDeudaCliente($cli_id)
  {
    $sql = "SELECT SUM(IF(hiv_deuda_Real != 0, hiv_deuda_Real, hiv_total))
            FROM pozettos_historico_venta
            WHERE hiv_fecha != '".$this->_fecha_contabilidad."'
            AND hiv_cli_id = '$cli_id'
            AND hiv_pago = 0
            AND hiv_es_tiempo_gratis = 0
            AND hiv_vigente = 1";
    $this->_conexionBD->ejecutarSQL($sql);
    return $this->_conexionBD->obtenerFilaComoCadena();
  }
  
  function actualizarTotal($hiv_id)
  {
    $sql = "UPDATE pozettos_historico_venta as hiv
            SET hiv.hiv_total = ( SELECT tas_precio
                                  FROM pozettos_tarifas_servicio
                                  WHERE tas_ser_id = hiv.hiv_ser_id
                                  AND tas_dus_minutos = hiv.hiv_dus_minutos
                                  LIMIT 1)
            WHERE hiv.hiv_id = '$hiv_id'";
                
    $this->_conexionBD->ejecutarSQL($sql);
    //echo $sql;
    if ($this->_conexionBD->obtenerNumeroFilasAfectadas())
      return true;
    else
      return false;
  }
  
  function obtenerJsonHoras($hiv_id)
  {
    $sql = "SELECT  time_format(hiv_hora, '%l:%i') as hiv_hora,
                    time_format(ADDTIME(hiv_hora, hiv_dus_minutos),'%l:%i') as hiv_hora_termina,
                    dus_texto,
                    hiv_total
            FROM pozettos_historico_venta, pozettos_duracion_servicio
            WHERE hiv_dus_minutos = dus_minutos
                  AND hiv_id = '".$hiv_id."'
                  AND hiv_vigente = 1
                  AND dus_vigente = 1";
    $this->_conexionBD->ejecutarSQL($sql);
    $arreglo_horas = $this->_conexionBD->obtenerFilaComoArregloAsociativo();
    $arreglo_horas['hiv_id'] = $hiv_id;
    return json_encode($arreglo_horas);
  }
  
  function actualizarCampoColor($id, $color_fila)
  {
    if($color_fila == "null")
      $color = "null";
    else
      $color = "'".$color_fila."'";

    $sql = "UPDATE pozettos_historico_venta
            SET hiv_color_fila = $color
            WHERE hiv_id = '$id'";

    $this->_conexionBD->ejecutarSQL($sql);
    if ($this->_conexionBD->obtenerNumeroFilasAfectadas())
      return json_encode(array("id"=>$id, "color"=>$color_fila));
    else
      return false;
  } 

  function actualizarEstadoPago($id_fila, $hiv_chk_pago, $hiv_chk_gratis, $ultimo_clic)
  {
    //echo "==>$hiv_chk_pago, $hiv_chk_gratis, $ultimo_clic";
    $hiv_pago = 0;
    $hiv_es_tiempo_gratis = 0;
    $set_adicional = "";
    if($ultimo_clic == "pago")
    {
      if($hiv_chk_pago == "true")
      {
        $hiv_es_tiempo_gratis = 0;
        $hiv_pago = 1;
        $set_adicional = ", hiv_deuda_real = 0";
      }
    }
    else if($ultimo_clic == "gratis")
    {
      if($hiv_chk_gratis == "true")
      {
        $hiv_es_tiempo_gratis = 1;
        $hiv_pago = 0;
        $set_adicional = ", hiv_deuda_real = 0";
      }
    }
  
    $sql = "UPDATE pozettos_historico_venta
            SET hiv_pago = '$hiv_pago',
            hiv_es_tiempo_gratis = '$hiv_es_tiempo_gratis'
            $set_adicional
            WHERE hiv_id = '$id_fila'";
    //echo $sql;
    $this->_conexionBD->ejecutarSQL($sql);
    if ($this->_conexionBD->obtenerNumeroFilasAfectadas())
      return json_encode(array("hiv_id"=>$id_fila, "ultimo_clic"=>$ultimo_clic));
    else
      return json_encode(array("hiv_id"=>$false));
  }
  
  function eliminarFila($id)
  {
    //el borrado es lógico
    $sql = "UPDATE pozettos_historico_venta
            SET hiv_vigente = 0
            WHERE hiv_id = '$id'";
    $this->_conexionBD->ejecutarSQL($sql);
    if ($this->_conexionBD->obtenerNumeroFilasAfectadas())
      return "hiv_fila_".$id;
    else
      return false;
  }

/**********************************
******* ACCIONES HISTORIAL  *******
***********************************/

  function agregarFilaHistorial($hiv_ser_id, $hiv_ser_tipo, $hiv_hora, $hiv_minuto, $hiv_meridiano, $hiv_dus_minutos, $hiv_total,  $hiv_fecha)
  {
    $sql = "INSERT INTO pozettos_historico_venta
            ( hiv_cli_id, hiv_ser_id, hiv_fecha, hiv_hora, hiv_ser_tipo,
              hiv_meridiano, hiv_total, hiv_dus_minutos)
            VALUES
            ( '1', '$hiv_ser_id','$hiv_fecha','$hiv_hora:$hiv_minuto:00', '$hiv_ser_tipo',
              '$hiv_meridiano', 0, '00:00:00')";
    $this->_conexionBD->ejecutarSQL($sql);
    //echo $sql;
    if ($this->_conexionBD->obtenerNumeroFilasAfectadas())
    {
      $sql = "SELECT  hiv1.hiv_id,
                      hiv1.hiv_cli_id,
                      hiv1.hiv_color_fila,
                      hiv1.hiv_pago,
                      hiv1.hiv_es_tiempo_gratis,
                      time_format(hiv1.hiv_hora, '%l:%i') as hiv_hora,
                      IF(hiv1.hiv_ser_tipo = 'servicio', dus_texto, null) as dus_texto,
                      IF(hiv1.hiv_ser_tipo = 'servicio', dus_minutos, null) as dus_minutos,
                      IF(hiv1.hiv_ser_tipo = 'servicio', time_format(ADDTIME(hiv1.hiv_hora, hiv1.hiv_dus_minutos),'%l:%i'), null) as hiv_hora_termina,
                      hiv1.hiv_total,
                      hiv1.hiv_deuda_real,
                      hiv1.hiv_observacion,
                      ser_nombre,
                      cli_nombre,
                      cli_apellido,
                      ( SELECT SUM(IF(hiv2.hiv_deuda_Real != 0, hiv2.hiv_deuda_Real, hiv2.hiv_total))
                        FROM pozettos_historico_venta AS hiv2
                        WHERE hiv2.hiv_fecha != '".$this->_fecha_contabilidad."'
                        AND hiv2.hiv_cli_id = hiv1.hiv_cli_id
                        AND hiv2.hiv_pago = 0
                        AND hiv2.hiv_es_tiempo_gratis = 0
                        AND hiv2.hiv_vigente
                      ) AS deuda_vieja
              FROM  pozettos_historico_venta as hiv1, pozettos_servicio, pozettos_cliente, pozettos_duracion_servicio
              WHERE hiv1.hiv_ser_id = ser_id
                    AND hiv1.hiv_dus_minutos = dus_minutos
                    AND hiv1.hiv_cli_id = cli_id
                    AND hiv1.hiv_fecha = '".$this->_fecha_contabilidad."'
                    AND hiv1.hiv_vigente = 1
              ORDER BY hiv1.hiv_id DESC LIMIT 1";
      $this->_conexionBD->ejecutarSQL($sql);
      $info_tupla_historico = $this->_conexionBD->obtenerFilaComoArregloAsociativo();

      //td's servicio
      if($info_tupla_historico['hiv_color_fila'])$color = $info_tupla_historico['hiv_color_fila'];
      else $color = "";
      $td_oculto_color = $this->_html->tag("td", "class='oculto'", array("<span id='hiv_color_oculto_".$info_tupla_historico['hiv_id']."'> $color</span>"));

      $td_oculto_id = $this->_html->tag("td", "class='oculto'", array("<span>".$info_tupla_historico['hiv_id']."</span>"));

      $input_color = $this->_html->tag("input", "title='Colocar un color a la fila' type='image' src='../imagenes/color.jpg' id='hiv_color_".$info_tupla_historico['hiv_id']."' class='boton_color'", "", true);
      $td_color = $this->_html->tag("td", "class='alineacion_centro'", array($input_color));

      $label_nombre = $this->_html->tag("label", "class='verdana letra_9'", array(utf8_encode($info_tupla_historico['ser_nombre'])));
      $td_nombre = $this->_html->tag("td", "class='alineacion_izquierda' title='Servicio prestado'", array($label_nombre));

      $label_hora = $this->_html->tag("label", "class='cursor_cruz'", array($info_tupla_historico['hiv_hora']));
      $td_hora = $this->_html->tag("td", "class='alineacion_centro verdana letra_9 cursor_cruz' id='hiv_hora_".$info_tupla_historico['hiv_id']."' onclick=\"editableHoraInicio('hiv_hora_".$info_tupla_historico['hiv_id']."',true);\" title='Hora en que se presta el servicio'", array($label_hora));

      $input_dus_minutos = $label_dus_minutos = $class = $onclick = "";
      if($info_tupla_historico['dus_minutos'])
      {
        $onclick = "onclick=\"editableDuracion('hiv_dus_minutos_".$info_tupla_historico['hiv_id']."',true);\"";
        $class = "class='alineacion_centro verdana letra_9 cursor_cruz'";
        $input_dus_minutos = $this->_html->tag("input", "type='hidden' value='".$info_tupla_historico['dus_minutos']."' id='hidden_hiv_dus_minutos_".$info_tupla_historico['hiv_id']."'", "", true);
        $label_dus_minutos = $this->_html->tag("label", "class='cursor_cruz'", array($info_tupla_historico['dus_texto']));
      }
      $td_dus_minutos = $this->_html->tag("td", "$class $onclick title='Duración del servicio prestado' id='hiv_dus_minutos_".$info_tupla_historico['hiv_id']."'", array($input_dus_minutos,$label_dus_minutos));

      $label_hora_termina = "";
      if($info_tupla_historico['hiv_hora_termina'])
        $label_hora_termina = $this->_html->tag("label", "", array($info_tupla_historico['hiv_hora_termina']));
      $td_hora_termina = $this->_html->tag("td", "class='alineacion_centro verdana letra_9' title='Hora en que se termina de prestar el servicio' id='hiv_hora_termina_".$info_tupla_historico['hiv_id']."'", array($label_hora_termina));

      $label_total = $this->_html->tag("label", "class='cursor_cruz'", array($info_tupla_historico['hiv_total']));
      $td_total = $this->_html->tag("td", "class='alineacion_derecha verdana letra_9 cursor_cruz' title='Total a pagar por el servicio' id='hiv_total_".$info_tupla_historico['hiv_id']."' onclick=\"editableTotal('hiv_total_".$info_tupla_historico['hiv_id']."',true);\"", array($label_total));

      $label_deuda_real = $this->_html->tag("label", "class='cursor_cruz'", array($info_tupla_historico['hiv_deuda_real']));
      $td_deuda_real = $this->_html->tag("td", "class='alineacion_derecha verdana letra_9 cursor_cruz' title='Lo que debe realmente del valor total' id='hiv_deuda_real_".$info_tupla_historico['hiv_id']."' onclick=\"editableDeudaReal('hiv_deuda_real_".$info_tupla_historico['hiv_id']."',true);\"", array($label_deuda_real));

      $checked_pago = $checked_gratis = $clase_celda_gratis = "";
      $clase_celda_pago = "celda_debe";//por defecto roja
      if($info_tupla_historico['hiv_pago'])
      {
        $checked_pago = "checked='checked'";
        $clase_celda_pago = "celda_pago";//si pago => verde
      }
      else if($info_tupla_historico['hiv_es_tiempo_gratis'])
      {
        $checked_gratis = "checked='checked'";
        $clase_celda_gratis = "celda_pago";//es gratis => verde
        $clase_celda_pago = "";//es gratis => en blanco
      }
      $input_pago = $this->_html->tag("input", "type='checkbox' id='hiv_chk_pago_".$info_tupla_historico['hiv_id']."' $checked_pago onchange=\"actualizarEstadoPago(".$info_tupla_historico['hiv_id'].",'pago');\"", "", true);
      $td_pago = $this->_html->tag("td", "class='alineacion_centro $clase_celda_pago' title='Ya pagó el total del servicio' id='hiv_pago_".$info_tupla_historico['hiv_id']."'", array($input_pago));

      $input_gratis = $this->_html->tag("input", "type='checkbox' id='hiv_chk_gratis_".$info_tupla_historico['hiv_id']."' $checked_gratis onchange=\"actualizarEstadoPago(".$info_tupla_historico['hiv_id'].",'gratis');\"", "", true);
      $td_gratis = $this->_html->tag("td", "class='alineacion_centro $clase_celda_gratis' title='No se cobra porque es gratis' id='hiv_gratis_".$info_tupla_historico['hiv_id']."'", array($input_gratis));

      $label_cliente = $this->_html->tag("label", "class='cursor_cruz'", array($info_tupla_historico['hiv_cli_id']));
      $img_deuda_vieja = "";
      if($info_tupla_historico['deuda_vieja'] && $info_tupla_historico['hiv_cli_id'] != "1")
        $img_deuda_vieja = $this->_html->tag("img", "id='cli_img_debe_".$info_tupla_historico['hiv_id']."' class='imagen_deuda' src='../imagenes/deuda.gif' title='Debe ".$info_tupla_historico['deuda_vieja']." de otros dias'", "", true);
      $span_deuda_vieja = $this->_html->tag("span", "id='cli_span_debe_".$info_tupla_historico['hiv_id']."'", array($img_deuda_vieja));
      $td_cliente = $this->_html->tag("td",
                                      "class='alineacion_centro verdana letra_9 cursor_cruz' title='".$info_tupla_historico['hiv_cli_id']." -> ".utf8_encode($info_tupla_historico['cli_nombre'])." ".utf8_encode($info_tupla_historico['cli_apellido'])."' id='cli_fila_".$info_tupla_historico['hiv_id']."' onclick=\"editableCliente('cli_fila_".$info_tupla_historico['hiv_id']."',true);\"",
                                      array($label_cliente,$span_deuda_vieja));

      $label_observacion = $this->_html->tag("label", "class='cursor_cruz'", array(utf8_encode($info_tupla_historico['hiv_observacion'])));
      $td_observacion = $this->_html->tag("td", "class='alineacion_izquierda verdana letra_9 cursor_cruz' title='Nota adicional si se necesita' id='hiv_observacion_".$info_tupla_historico['hiv_id']."' onclick=\"editableObservacion('hiv_observacion_".$info_tupla_historico['hiv_id']."',true);\"", array($label_observacion));

      $img_eliminar = $this->_html->tag("img", "class='imagen_delete' src='../imagenes/delete.png'", "", true);
      $button_eliminar = $this->_html->tag("button", "class='boton_delete' onclick=\"eliminarFila(".$info_tupla_historico['hiv_id'].");\"", array($img_eliminar));
      $td_eliminar = $this->_html->tag("td", "class='alineacion_centro' title='Eliminar esta fila'", array($button_eliminar));

      $estilo_fila = "";
      if($info_tupla_historico['hiv_color_fila'])
        $estilo_fila = "style='{background: ".$info_tupla_historico['hiv_color_fila'].";}'";
        
      //tr servicio
      return $this->_html->tag( "tr",
                                "id='hiv_fila_".$info_tupla_historico['hiv_id']."' name='fila_historico' $estilo_fila",
                                array($td_oculto_color,$td_oculto_id,
                                      $td_color,$td_nombre,$td_hora,
                                      $td_dus_minutos,$td_hora_termina,
                                      $td_total,$td_deuda_real,$td_pago,$td_gratis,
                                      $td_cliente,$td_observacion,$td_eliminar));
    }
    else
      return false;
  }

  function actualizarHistorialVentas()
  {
    $sql = "SELECT  hiv1.hiv_id,
                    hiv1.hiv_cli_id,
                    hiv1.hiv_color_fila,
                    hiv1.hiv_pago,
                    hiv1.hiv_es_tiempo_gratis,
                    time_format(hiv1.hiv_hora, '%l:%i') as hiv_hora,
                    IF(hiv1.hiv_ser_tipo = 'servicio', dus_texto, null) as dus_texto,
                    IF(hiv1.hiv_ser_tipo = 'servicio', dus_minutos, null) as dus_minutos,
                    IF(hiv1.hiv_ser_tipo = 'servicio', time_format(ADDTIME(hiv1.hiv_hora, hiv1.hiv_dus_minutos),'%l:%i'), null) as hiv_hora_termina,
                    hiv1.hiv_total, 
                    hiv1.hiv_deuda_real,
                    hiv1.hiv_observacion, 
                    ser_nombre,
                    cli_nombre,
                    cli_apellido,
                    ( SELECT SUM(IF(hiv2.hiv_deuda_Real != 0, hiv2.hiv_deuda_Real, hiv2.hiv_total))
                      FROM pozettos_historico_venta AS hiv2
                      WHERE hiv2.hiv_fecha != '".$this->_fecha_contabilidad."'
                      AND hiv2.hiv_cli_id = hiv1.hiv_cli_id
                      AND hiv2.hiv_pago = 0
                      AND hiv2.hiv_es_tiempo_gratis = 0
                      AND hiv2.hiv_vigente
                    ) AS deuda_vieja
            FROM  pozettos_historico_venta as hiv1, pozettos_servicio, pozettos_cliente, pozettos_duracion_servicio
            WHERE hiv1.hiv_ser_id = ser_id
            AND hiv1.hiv_dus_minutos = dus_minutos
            AND hiv1.hiv_cli_id = cli_id
            AND hiv1.hiv_fecha = '".$this->_fecha_contabilidad."'
            AND hiv1.hiv_vigente = 1
            ORDER BY hiv1.hiv_color_fila DESC, hiv1.hiv_id DESC";
    $this->_conexionBD->ejecutarSQL($sql);

    $filas_servicios = "";
    while($info_tupla_historico = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
    {
      //td's servicio
      if($info_tupla_historico['hiv_color_fila'])$color = $info_tupla_historico['hiv_color_fila'];
      else $color = " ";
      $td_oculto_color = $this->_html->tag("td", "class='oculto'", array("<span id='hiv_color_oculto_".$info_tupla_historico['hiv_id']."'> $color</span>"));
      
      $td_oculto_id = $this->_html->tag("td", "class='oculto'", array("<span>".$info_tupla_historico['hiv_id']."</span>"));

      $input_color = $this->_html->tag("input", "title='Colocar un color a la fila' type='image' src='../imagenes/color.jpg' id='hiv_color_".$info_tupla_historico['hiv_id']."' class='boton_color'", "", true);
      $td_color = $this->_html->tag("td", "class='alineacion_centro'", array($input_color));

      $label_nombre = $this->_html->tag("label", "class='verdana letra_9'", array(utf8_encode($info_tupla_historico['ser_nombre'])));
      $td_nombre = $this->_html->tag("td", "class='alineacion_izquierda' title='Servicio prestado'", array($label_nombre));

      $label_hora = $this->_html->tag("label", "class='cursor_cruz'", array($info_tupla_historico['hiv_hora']));
      $td_hora = $this->_html->tag("td", "class='alineacion_centro verdana letra_9 cursor_cruz' id='hiv_hora_".$info_tupla_historico['hiv_id']."' onclick=\"editableHoraInicio('hiv_hora_".$info_tupla_historico['hiv_id']."',true);\" title='Hora en que se presta el servicio'", array($label_hora));

      $input_dus_minutos = $label_dus_minutos = $class = $onclick = "";
      if($info_tupla_historico['dus_minutos'])
      {
        $onclick = "onclick=\"editableDuracion('hiv_dus_minutos_".$info_tupla_historico['hiv_id']."',true);\"";
        $class = "class='alineacion_centro verdana letra_9 cursor_cruz'";
        $input_dus_minutos = $this->_html->tag("input", "type='hidden' value='".$info_tupla_historico['dus_minutos']."' id='hidden_hiv_dus_minutos_".$info_tupla_historico['hiv_id']."'", "", true);
        $label_dus_minutos = $this->_html->tag("label", "class='cursor_cruz'", array($info_tupla_historico['dus_texto']));
      }
      $td_dus_minutos = $this->_html->tag("td", "$class $onclick title='Duración del servicio prestado' id='hiv_dus_minutos_".$info_tupla_historico['hiv_id']."'", array($input_dus_minutos,$label_dus_minutos));

      $label_hora_termina = "";
      if($info_tupla_historico['hiv_hora_termina'])
        $label_hora_termina = $this->_html->tag("label", "", array($info_tupla_historico['hiv_hora_termina']));
      $td_hora_termina = $this->_html->tag("td", "class='alineacion_centro verdana letra_9' title='Hora en que se termina de prestar el servicio' id='hiv_hora_termina_".$info_tupla_historico['hiv_id']."'", array($label_hora_termina));

      $label_total = $this->_html->tag("label", "class='cursor_cruz'", array($info_tupla_historico['hiv_total']));
      $td_total = $this->_html->tag("td", "class='alineacion_derecha verdana letra_9 cursor_cruz' title='Total a pagar por el servicio' id='hiv_total_".$info_tupla_historico['hiv_id']."' onclick=\"editableTotal('hiv_total_".$info_tupla_historico['hiv_id']."',true);\"", array($label_total));

      $label_deuda_real = $this->_html->tag("label", "class='cursor_cruz'", array($info_tupla_historico['hiv_deuda_real']));
      $td_deuda_real = $this->_html->tag("td", "class='alineacion_derecha verdana letra_9 cursor_cruz' title='Lo que debe realmente del valor total' id='hiv_deuda_real_".$info_tupla_historico['hiv_id']."' onclick=\"editableDeudaReal('hiv_deuda_real_".$info_tupla_historico['hiv_id']."',true);\"", array($label_deuda_real));

      $checked_pago = $checked_gratis = $clase_celda_gratis = "";
      $clase_celda_pago = "celda_debe";//por defecto roja
      if($info_tupla_historico['hiv_pago'])
      {
        $checked_pago = "checked='checked'";
        $clase_celda_pago = "celda_pago";//si pago => verde
      }
      else if($info_tupla_historico['hiv_es_tiempo_gratis'])
      {
        $checked_gratis = "checked='checked'";
        $clase_celda_gratis = "celda_pago";//es gratis => verde
        $clase_celda_pago = "";//es gratis => en blanco
      }
      $input_pago = $this->_html->tag("input", "type='checkbox' id='hiv_chk_pago_".$info_tupla_historico['hiv_id']."' $checked_pago onchange=\"actualizarEstadoPago(".$info_tupla_historico['hiv_id'].",'pago');\"", "", true);
      $td_pago = $this->_html->tag("td", "class='alineacion_centro $clase_celda_pago' title='Ya pagó el total del servicio' id='hiv_pago_".$info_tupla_historico['hiv_id']."'", array($input_pago));

      $input_gratis = $this->_html->tag("input", "type='checkbox' id='hiv_chk_gratis_".$info_tupla_historico['hiv_id']."' $checked_gratis onchange=\"actualizarEstadoPago(".$info_tupla_historico['hiv_id'].",'gratis');\"", "", true);
      $td_gratis = $this->_html->tag("td", "class='alineacion_centro $clase_celda_gratis' title='No se cobra porque es gratis' id='hiv_gratis_".$info_tupla_historico['hiv_id']."'", array($input_gratis));

      $label_cliente = $this->_html->tag("label", "class='cursor_cruz'", array($info_tupla_historico['hiv_cli_id']));
      $img_deuda_vieja = "";
      if($info_tupla_historico['deuda_vieja'] && $info_tupla_historico['hiv_cli_id'] != "1")
        $img_deuda_vieja = $this->_html->tag("img", "id='cli_img_debe_".$info_tupla_historico['hiv_id']."' class='imagen_deuda' src='../imagenes/deuda.gif' title='Debe ".$info_tupla_historico['deuda_vieja']." de otros dias'", "", true);
      $span_deuda_vieja = $this->_html->tag("span", "id='cli_span_debe_".$info_tupla_historico['hiv_id']."'", array($img_deuda_vieja));
      $td_cliente = $this->_html->tag("td",
                                      "class='alineacion_centro verdana letra_9 cursor_cruz' title='".$info_tupla_historico['hiv_cli_id']." -> ".utf8_encode($info_tupla_historico['cli_nombre'])." ".utf8_encode($info_tupla_historico['cli_apellido'])."' id='cli_fila_".$info_tupla_historico['hiv_id']."' onclick=\"editableCliente('cli_fila_".$info_tupla_historico['hiv_id']."',true);\"",
                                      array($label_cliente,$span_deuda_vieja));

      $label_observacion = $this->_html->tag("label", "class='cursor_cruz'", array(utf8_encode($info_tupla_historico['hiv_observacion'])));
      $td_observacion = $this->_html->tag("td", "class='alineacion_izquierda verdana letra_9 cursor_cruz' title='Nota adicional si se necesita' id='hiv_observacion_".$info_tupla_historico['hiv_id']."' onclick=\"editableObservacion('hiv_observacion_".$info_tupla_historico['hiv_id']."',true);\"", array($label_observacion));

      $img_eliminar = $this->_html->tag("img", "class='imagen_delete' src='../imagenes/delete.png'", "", true);
      $button_eliminar = $this->_html->tag("button", "class='boton_delete' onclick=\"eliminarFila(".$info_tupla_historico['hiv_id'].");\"", array($img_eliminar));
      $td_eliminar = $this->_html->tag("td", "class='alineacion_centro' title='Eliminar esta fila'", array($button_eliminar));

      $estilo_fila = "";
      if($info_tupla_historico['hiv_color_fila'])
        $estilo_fila = "style='{background: ".$info_tupla_historico['hiv_color_fila'].";}'";
      //tr servicio
      $filas_servicios .= $this->_html->tag( "tr",
                                            "id='hiv_fila_".$info_tupla_historico['hiv_id']."' name='fila_historico' $estilo_fila",
                                            array($td_oculto_color,$td_oculto_id,
                                                  $td_color,$td_nombre,$td_hora,
                                                  $td_dus_minutos,$td_hora_termina,
                                                  $td_total,$td_deuda_real,$td_pago,$td_gratis,
                                                  $td_cliente,$td_observacion,$td_eliminar));
    }
    return $filas_servicios;
  }

/**********************************
******* ACCIONES TIMERS     *******
***********************************/
  /*
  function obtenerInfoTimers()
  {
    $sql = "SELECT tim_id, 
            tim_dus_minutos,
            tim_inicia, 
            tim_finaliza,
            TIMEDIFF(CURRENT_TIMESTAMP , tim_inicia) as tim_lleva, 
            TIMEDIFF(tim_finaliza , CURRENT_TIMESTAMP) as tim_falta, 
            tim_es_incremental, 
            tim_esta_ejecutando
            FROM pozettos_timer";
                
    $this->_conexionBD->ejecutarSQL($sql);
    $arreglo_timers = array();
    
    while($info_timer = $this->_conexionBD->obtenerFilaComoArregloAsociativo())
    {
      $arreglo_timers[] = $info_timer;
    }
    return $arreglo_timers;
  }*/
}
?>
