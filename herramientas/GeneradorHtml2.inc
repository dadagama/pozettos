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

class GeneradorHtml2
{
  function printHtml($arreglo_tags = array())
  {
    foreach ($arreglo_tags AS $tag)
      echo $tag;
  }
  
  function tag($tag, $attrs="", $childrens=array(), $one_line=false)
  {
    if($one_line)
      $html = "<$tag $attrs />";
    else
    {
      $html = "<$tag $attrs>";
      if($childrens)
        foreach($childrens AS $children)
            $html .= $children;            
      $html .= "</$tag>";
    }
    return $html;       
  }
  
  /**
  * Función auxiliar que carga el archivo javascript del módulo.
  * @param	$modulo	nombre del módulo y al mismo tiempo del archivo javascript.
  */	
	function cargarModuloJS($modulo)
	{
		echo $this->tag("script", "type='text/javascript' src='../modulo_$modulo/$modulo.js'");
	}
	
	/**
  * Función auxiliar que carga un archivo javascript.
  * @param	$ruta_archivo	ruta del archivo javascript.
  */	
	function cargarHerramientaJS($ruta_archivo)
	{
		$this->tag("script", "type='text/javascript' src='$ruta_archivo.js'");
	}
}
?>