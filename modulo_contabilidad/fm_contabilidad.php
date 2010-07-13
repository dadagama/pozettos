<html>
  <head>
    <link rel="stylesheet" type="text/css" href="../modulo_contabilidad/contabilidad.css"/>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
  </head>
  <body>
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

  session_start();
    
  $_SESSION['modulo'] = "contabilidad";
  if($_REQUEST['con_fecha'])
    $_SESSION['fecha_contabilidad'] = $_REQUEST['con_fecha'];
  else if($_SESSION['fecha_contabilidad']){}
  else
    $_SESSION['fecha_contabilidad'] = date("Y-m-d");

  require_once("../herramientas/GeneradorHtml2.inc");
  $html = new GeneradorHtml2();
  
  require_once("../modulo_contabilidad/Contabilidad.inc");
  $objetoContabilidad = new Contabilidad($_SESSION['arregloParametros'], $_SESSION['fecha_contabilidad']);
  
  $html->cargarModuloJS($_SESSION['modulo']);
  
  require_once("../conexiones/ConexionBDMySQL.inc");
  $conexion_bd_bozettos = new ConexionBDMySQL($_SESSION['arregloParametros']);
  $conexion_bd_bozettos->conectar();
  
    //tr contabilidad
        $lbl_contabilidad = $html->tag("label", "", array("Contabilidad"));
        if($_SESSION['fecha_contabilidad'] != date("Y-m-d"))
          $clase_fecha = "class='fecha_otro_dia'";
        $lbl_fecha = $html->tag("label", "id='lbl_fecha_contabilidad' ".$clase_fecha, array($html->obtenerFechaTextual($_SESSION['fecha_contabilidad'], true, true, true, true)));
        $inp_fecha = $html->tag("input", "type='hidden' id='fecha_contabilidad' value='".$_SESSION['fecha_contabilidad']."'", "", true);
      $td_fecha = $html->tag("td", "class='alineacion_centro' colspan='4'", array($lbl_contabilidad,$html->espacios(2),$lbl_fecha,$inp_fecha));
    $tr_fecha = $html->tag("tr", "", array($td_fecha));
    //tr saldo titan
        $lbl_saldo_titan = $html->tag("label", "", array("Saldo Inicial TITAN:"));
      $td_lbl_saldo = $html->tag("td", "class='alineacion_izquierda'", array($lbl_saldo_titan));
        $lbl_valor_saldo = $html->tag("label", "id='sit_saldo' class='verdana letra_9 cursor_cruz' ondblclick='editableSaldoTitan(true);'");
      $td_valor_saldo = $html->tag("td", "class='alineacion_centro ancho_140'", array($lbl_valor_saldo));
    //tr egreso diario
        $lbl_egreso = $html->tag("label", "", array("Plata que sale:"));
      $td_lbl_egreso = $html->tag("td", "class='alineacion_izquierda'", array($lbl_egreso));
        $lbl_valor_egreso = $html->tag("label", "id='egd_saldo' class='verdana letra_9 cursor_cruz' ondblclick='editableSaldoEgresos(true);'");
      $td_valor_egreso = $html->tag("td", "class='alineacion_centro ancho_140'", array($lbl_valor_egreso));
    $tr_saldos = $html->tag("tr", "", array($td_lbl_saldo,$td_valor_saldo,$td_lbl_egreso,$td_valor_egreso));
  //tabla titulo
  $table_titulo = $html->tag("table", "class='tbl_titulo tabla_centrada'", array($tr_fecha,$tr_saldos));

  /*TABLA PRODUCTOS Y SERVICIOS*/
      $td_servicios = $html->tag("td", "", array($objetoContabilidad->obtenerTablaServicios()));
    $tr_servicios = $html->tag("tr", "", array($td_servicios));
  $table_servicios = $html->tag("table", "class='tabla_centrada'", array($tr_servicios));
  
//   $html->tag("table", array("class"=>"tabla_centrada"));
//     $html->tag("tr");
      // $html->tag("td", array("class"=>"vertical_arriba"));
        // $html->tag("table", array("class"=>"fondo_azul"));
              // /* TIMER 0 */
              // $html->tag("tr");
                // $html->tag("td");
                  // $html->tag("label", array("class"=>"label_formulario"));
                    // $html->printText("Xbox 1");
                  // $html->end("label");
                // $html->end("td");
                // $html->tag("td");
                  // $html->tag("input", array("id"=>"tim_duracion_horas_0", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
                  // $html->tag("label", array("class"=>"label_formulario"));
                    // $html->printText(":");
                  // $html->end("label");
                  // $html->tag("input", array("id"=>"tim_duracion_minutos_0", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
                  // $html->tag("label", array("class"=>"label_formulario"));
                    // $html->printText(":");
                  // $html->end("label");
                  // $html->tag("input", array("id"=>"tim_duracion_segundos_0", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
                // $html->end("td");
                // $html->tag("td");
                  // $html->tag("button", array("id"=>"btn_play_pause_0", "class"=>"boton_timer", "onclick"=>"IniciarCrono(0);"));
                    // $html->tag("img", array("id"=>"img_play_pause_0", "src"=>"../imagenes/play.jpg", "class"=>"imagen_timer"), true);
                  // $html->end("button");
                // $html->end("td");
                // $html->tag("td");
                  // $html->tag("button", array("class"=>"boton_timer", "onclick"=>"InicializarCrono(0);"));
                    // $html->tag("img", array("src"=>"../imagenes/stop.jpg", "class"=>"imagen_timer"), true);
                  // $html->end("button");
                // $html->end("td");
              // $html->end("tr");
            // $html->end("table");
          // $html->end("td");
//     $html->end("tr");
//   $html->end("table");

        //th's encabezados
        $th_oculto = $html->tag("th", "class='oculto'",array("<label class='label_formulario'>coso</label>"));//se utilizan 2 de estos: para id y para color_fila
        $th_color = $html->tag("th", "class='fondo_azul ancho_scroll'");
        $th_servicio = $html->tag("th", "class='fondo_azul alineacion_centro ancho_140'",array("<label class='label_formulario'>Servicio</label>"));
        $th_hora = $html->tag("th", "class='fondo_azul alineacion_centro ancho_70'",array("<label class='label_formulario'>Hora</label>"));
        $th_duracion = $html->tag("th", "class='fondo_azul alineacion_centro ancho_70'",array("<label class='label_formulario'>Duración</label>"));
        $th_termina = $html->tag("th", "class='fondo_azul alineacion_centro ancho_70'",array("<label class='label_formulario'>Termina</label>"));
        $th_total = $html->tag("th", "class='fondo_azul alineacion_centro ancho_50'",array("<label class='label_formulario'>Total</label>"));
        $th_deuda_real = $html->tag("th", "class='fondo_azul alineacion_centro ancho_50'",array("<label class='label_formulario'>Deuda</label><br/><label class='label_formulario'>Real</label>"));        
        $th_pago = $html->tag("th", "class='fondo_azul alineacion_centro ancho_50'",array("<label class='label_formulario'>Pago</label>"));
        $th_gratis = $html->tag("th", "class='fondo_azul alineacion_centro ancho_50'",array("<label class='label_formulario'>Gratis</label>"));
        $th_cliente = $html->tag("th", "class='fondo_azul alineacion_centro ancho_70'",array("<label class='label_formulario'>Cliente</label>"));
        $th_observacion = $html->tag("th", "class='fondo_azul alineacion_centro'",array("<label class='label_formulario'>Observación</label>"));
        $th_eliminar = $html->tag("th", "class='fondo_azul ancho_25'");
      //tr encabezados
      $tr_encabezados = $html->tag("tr", "", array( $th_oculto,$th_oculto,$th_color,$th_servicio,$th_hora,$th_duracion,$th_termina,
                                                  $th_total,$th_deuda_real,$th_pago,$th_gratis,$th_cliente,$th_observacion,$th_eliminar));
    //thead encabezados
    $thead_encabezados = $html->tag("thead", "", array($tr_encabezados));
    //tbody historial
    $tbody_historial = $html->tag("tbody", "id='historial_ventas' class='cuerpo_historial'");
  //table historial
  $table_historial = $html->tag("table", "id='tbl_historial' class='zona_historial ancho_100p'", array($thead_encabezados,$tbody_historial));

  $contenido_modulo = "";
  if($viene_de_icono)//hizo click en el menu
    echo $table_titulo, $table_servicios, $table_historial;
  else//actualizo la pagina f5
  {
    $contenido_modulo .= $table_titulo;
    $contenido_modulo .= $table_servicios;
    $contenido_modulo .= $table_historial;
  }
?>

  </body>
</html>