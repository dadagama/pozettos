<html>
  <head>
    <link rel="stylesheet" type="text/css" href="../modulo_contabilidad/contabilidad.css"/>
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
  else
    $_SESSION['fecha_contabilidad'] = date("Y-m-d");
  require_once("../herramientas/GeneradorHtml.inc");
  $html = new GeneradorHtml();
  
  require_once("../modulo_contabilidad/Contabilidad.inc");
  $objetoContabilidad = new Contabilidad($_SESSION['arregloParametros'], $_SESSION['fecha_contabilidad']);
  
  $html->cargarModuloJS($_SESSION['modulo']);
  
  require_once("../conexiones/ConexionBDMySQL.inc");
  $conexion_bd_bozettos = new ConexionBDMySQL($_SESSION['arregloParametros']);
  $conexion_bd_bozettos->conectar();
  
  $html->tag("table",array("class"=>"tbl_titulo tabla_centrada"));
    $html->tag("tr");
      $html->tag("td", array("class"=>"alineacion_centro"));
        $html->tag("label");
          $html->printText("Contabilidad");
          $html->espacios(2);
        $html->end("label");
        if($_SESSION['fecha_contabilidad'] != date("Y-m-d"))
          $clase_fecha = "fecha_otro_dia";
        $html->tag("label", array("id"=>"lbl_fecha_contabilidad", "class"=>$clase_fecha));
          $html->printText($html->obtenerFechaTextual($_SESSION['fecha_contabilidad'], true, true, true, true));
          $html->tag("input", array("type"=>"hidden", "id"=>"fecha_contabilidad", "value"=>$_SESSION['fecha_contabilidad']));
        $html->end("label");
      $html->end("td");
    $html->end("tr");
    $html->tag("tr");
      $html->tag("td", array("class"=>"alineacion_centro"));
        $html->tag("label");
          $html->printText("Saldo Inicial TITAN:");
          $html->espacios(2);
        $html->end("label");
        $html->tag("label", array("id"=>"sit_saldo", "class"=>"verdana letra_9 cursor_cruz", "ondblclick"=>"editableSaldoTitan(true);"));
        $html->end("label");
      $html->end("td");
    $html->end("tr");
  $html->end("table");
  
  /*TABLA PRODUCTOS Y SERVICIOS*/
  $html->tag("table", array("class"=>"tabla_centrada"));
    $html->tag("tr");
      $html->tag("td");
        $objetoContabilidad->obtenerTablaServicios();
      $html->end("td");
      
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
              
              // /* TIMER 1 */
              // $html->tag("tr");
                
                // $html->tag("td");
                  // $html->tag("label", array("class"=>"label_formulario"));
                    // $html->printText("Xbox 2");
                  // $html->end("label");
                // $html->end("td");
                // $html->tag("td");
                  // $html->tag("input", array("id"=>"tim_duracion_horas_1", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
                  // $html->tag("label", array("class"=>"label_formulario"));
                    // $html->printText(":");
                  // $html->end("label");
                  // $html->tag("input", array("id"=>"tim_duracion_minutos_1", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
                  // $html->tag("label", array("class"=>"label_formulario"));
                    // $html->printText(":");
                  // $html->end("label");
                  // $html->tag("input", array("id"=>"tim_duracion_segundos_1", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
                // $html->end("td");
                
                // $html->tag("td");
                  // $html->tag("button", array("id"=>"btn_play_pause_1", "class"=>"boton_timer", "onclick"=>"IniciarCrono(1);"));
                    // $html->tag("img", array("id"=>"img_play_pause_1", "src"=>"../imagenes/play.jpg", "class"=>"imagen_timer"), true);
                  // $html->end("button");
                // $html->end("td");
                
                // $html->tag("td");
                  // $html->tag("button", array("class"=>"boton_timer", "onclick"=>"InicializarCrono(1);"));
                    // $html->tag("img", array("src"=>"../imagenes/stop.jpg", "class"=>"imagen_timer"), true);
                  // $html->end("button");
                // $html->end("td");
              // $html->end("tr");
            
              // /* TIMER 2 */
              // $html->tag("tr");
                
                // $html->tag("td");
                  // $html->tag("label", array("class"=>"label_formulario"));
                    // $html->printText("Play 1");
                  // $html->end("label");
                // $html->end("td");
                // $html->tag("td");
                  // $html->tag("input", array("id"=>"tim_duracion_horas_2", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
                  // $html->tag("label", array("class"=>"label_formulario"));
                    // $html->printText(":");
                  // $html->end("label");
                  // $html->tag("input", array("id"=>"tim_duracion_minutos_2", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
                  // $html->tag("label", array("class"=>"label_formulario"));
                    // $html->printText(":");
                  // $html->end("label");
                  // $html->tag("input", array("id"=>"tim_duracion_segundos_2", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
                // $html->end("td");
                
                // $html->tag("td");
                  // $html->tag("button", array("id"=>"btn_play_pause_2", "class"=>"boton_timer", "onclick"=>"IniciarCrono(2);"));
                    // $html->tag("img", array("id"=>"img_play_pause_2", "src"=>"../imagenes/play.jpg", "class"=>"imagen_timer"), true);
                  // $html->end("button");
                // $html->end("td");
                
                // $html->tag("td");
                  // $html->tag("button", array("class"=>"boton_timer", "onclick"=>"InicializarCrono(2);"));
                    // $html->tag("img", array("src"=>"../imagenes/stop.jpg", "class"=>"imagen_timer"), true);
                  // $html->end("button");
                // $html->end("td");
              // $html->end("tr");
              
              // /* TIMER 3 */
              // $html->tag("tr");
                
                // $html->tag("td");
                  // $html->tag("label", array("class"=>"label_formulario"));
                    // $html->printText("Play 2");
                  // $html->end("label");
                // $html->end("td");
                // $html->tag("td");
                  // $html->tag("input", array("id"=>"tim_duracion_horas_3", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
                  // $html->tag("label", array("class"=>"label_formulario"));
                    // $html->printText(":");
                  // $html->end("label");
                  // $html->tag("input", array("id"=>"tim_duracion_minutos_3", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
                  // $html->tag("label", array("class"=>"label_formulario"));
                    // $html->printText(":");
                  // $html->end("label");
                  // $html->tag("input", array("id"=>"tim_duracion_segundos_3", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
                // $html->end("td");
                
                // $html->tag("td");
                  // $html->tag("button", array("id"=>"btn_play_pause_3", "class"=>"boton_timer", "onclick"=>"IniciarCrono(3);"));
                    // $html->tag("img", array("id"=>"img_play_pause_3", "src"=>"../imagenes/play.jpg", "class"=>"imagen_timer"), true);
                  // $html->end("button");
                // $html->end("td");
                
                // $html->tag("td");
                  // $html->tag("button", array("class"=>"boton_timer", "onclick"=>"InicializarCrono(3);"));
                    // $html->tag("img", array("src"=>"../imagenes/stop.jpg", "class"=>"imagen_timer"), true);
                  // $html->end("button");
                // $html->end("td");
              // $html->end("tr");
              
              // /* TIMER 4 */
              // $html->tag("tr");
          
                // $html->tag("td");
                  // $html->tag("label", array("class"=>"label_formulario"));
                    // $html->printText("Otro");
                  // $html->end("label");
                // $html->end("td");
                
                // $html->tag("td");
                  // $html->tag("input", array("id"=>"tim_duracion_horas_4", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
                  // $html->tag("label", array("class"=>"label_formulario"));
                    // $html->printText(":");
                  // $html->end("label");
                  // $html->tag("input", array("id"=>"tim_duracion_minutos_4", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
                  // $html->tag("label", array("class"=>"label_formulario"));
                    // $html->printText(":");
                  // $html->end("label");
                  // $html->tag("input", array("id"=>"tim_duracion_minutos_4", "type"=>"text", "class"=>"input_timer verdana letra_9", "maxlength"=>"2"), true);
                // $html->end("td");
                
                // $html->tag("td");
                  // $html->tag("button", array("id"=>"btn_play_pause_4", "class"=>"boton_timer", "onclick"=>"IniciarCrono(4);"));
                    // $html->tag("img", array("id"=>"img_play_pause_4", "src"=>"../imagenes/play.jpg", "class"=>"imagen_timer"), true);
                  // $html->end("button");
                // $html->end("td");
                
                // $html->tag("td");
                  // $html->tag("button", array("class"=>"boton_timer", "onclick"=>"InicializarCrono(4);"));
                    // $html->tag("img", array("src"=>"../imagenes/stop.jpg", "class"=>"imagen_timer"), true);
                  // $html->end("button");
                // $html->end("td");
              // $html->end("tr");

            // $html->end("table");
          // $html->end("td");

    $html->end("tr");
  $html->end("table");


  $html->tag("table",array("id"=>"tbl_historial", "class"=>"zona_historial ancho_100p"));
  
  //ENCABEZADOS HISTORIAL   
    $html->tag("thead");
      $html->tag("tr");
     
        $html->tag("th", array("class"=>"oculto"));
        $html->end("th");
        
        $html->tag("th", array("class"=>"oculto"));
        $html->end("th");
     
        $html->tag("th", array("class"=>"fondo_azul ancho_scroll"));
        $html->end("th");
       
        $html->tag("th", array("class"=>"fondo_azul alineacion_centro ancho_140"));
         $html->tag("label", array("class"=>"label_formulario"));
           $html->printText("Servicio");
         $html->end("label");
        $html->end("th");
        
        $html->tag("th", array("class"=>"fondo_azul alineacion_centro ancho_70"));
         $html->tag("label", array("class"=>"label_formulario"));
           $html->printText("Hora");
         $html->end("label");
        $html->end("th");
        
        $html->tag("th", array("class"=>"fondo_azul alineacion_centro ancho_70"));
         $html->tag("label", array("class"=>"label_formulario"));
           $html->printText("Duración");
         $html->end("label");
        $html->end("th");
        
        $html->tag("th", array("class"=>"fondo_azul alineacion_centro ancho_70"));
         $html->tag("label", array("class"=>"label_formulario"));
           $html->printText("Termina");
         $html->end("label");
        $html->end("th");
        
        $html->tag("th", array("class"=>"fondo_azul alineacion_centro ancho_50"));
         $html->tag("label", array("class"=>"label_formulario"));
           $html->printText("Total");
         $html->end("label");
        $html->end("th");
        
        $html->tag("th", array("class"=>"fondo_azul alineacion_centro ancho_50"));
         $html->tag("label", array("class"=>"label_formulario"));
           $html->printText("Pagó");
         $html->end("label");
        $html->end("th");
        
        $html->tag("th", array("class"=>"fondo_azul alineacion_centro ancho_50"));
         $html->tag("label", array("class"=>"label_formulario"));
           $html->printText("Gratis");
         $html->end("label");
        $html->end("th");
        
        $html->tag("th", array("class"=>"fondo_azul alineacion_centro ancho_70"));
         $html->tag("label", array("class"=>"label_formulario"));
           $html->printText("Cliente");
         $html->end("label");
        $html->end("th");
        
        $html->tag("th", array("class"=>"fondo_azul alineacion_centro"));
         $html->tag("label", array("class"=>"label_formulario"));
           $html->printText("Observación");
         $html->end("label");
        $html->end("th");
        
        $html->tag("th", array("class"=>"fondo_azul"));
        $html->end("th");
       
       // $html->tag("th", array("class"=>"ancho_scroll"));
       // $html->end("th");
      $html->end("tr");
   $html->end("thead");
   
   $html->tag("tbody", array("id"=>"historial_ventas", "class"=>"cuerpo_historial"));
     
   $html->end("tbody");
   
  $html->end("table");
?>

  </body>
</html>