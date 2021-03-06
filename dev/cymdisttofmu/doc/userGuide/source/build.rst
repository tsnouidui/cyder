.. highlight:: rest

.. _build:

Creating an FMU
===============

This chapter describes how to create a Functional Mockup Unit, starting from a CYMDIST XML input file.
It assumes you have followed the :doc:`installation` instructions, and that you have created the CYMDIST 
model description file  following the :doc:`bestPractice` guidelines.


Command-line use
^^^^^^^^^^^^^^^^

To create an FMU,
open a command-line window (see :doc:`notation`).
The standard invocation of the CYMDISTToFMU tool is:

.. code-block:: none

  > python  <scriptDir>CYMDISTToFMU.py <input-file-path> 

where ``scriptDir`` is the path to the scripts directory of CYMDISTToFMU.
This is the ``parser`` subdirectory of the installation directory.
See :doc:`installation` for details.

An example of invoking ``CYMDISTToFMU.py`` on Windows is 

.. code-block:: none

  # Windows:
  > python parser\CYMDISTToFMU.py test.xml

All file paths can be absolute or relative.
For readability, the rest of these instructions omit the paths to the script and input files.

.. note:: If any file path contains spaces, then it must be surrounded with double quotes.

Script ``CYMDISTToFMU.py`` supports the following command-line switches:

+----------------------------------------------------+----------------------------------------------------------+
| option <arguments>                                 | Purpose                                                 |
+====================================================+==========================================================+
| <input-file-path>                                  | Path to the input file (if not provided, a default input |   
|                                                    | file which is in 					|
|                                                    | ``parser\utilities\CYMDISTModelDescription.xml``		|
|						     | will be used.						|
+----------------------------------------------------+----------------------------------------------------------+
| -h                             		     | Show help and explanation on how to use this function.   |   
+----------------------------------------------------+----------------------------------------------------------+


The main functions of CYMDISTToFMU are

 - reading, validating, and parsing the CYMDIST XML input file. 
   This includes removing and replacing invalid characters in variable names such as ``*+-`` with ``_``,
 - writing Modelica code with valid inputs and outputs names,
 - invoking Dymola to compile the :term:`Modelica` code as an FMU for co-simulation 2.0.

.. note:: 

  In the process of creating the FMU, CYMDISTToFMU will rewrite the model description file 
  generated by Dymola to include ``needsExecutionTool=true`` attribute in the FMU capabilities of the CYMDIST FMU. 
  This is currently not supported by default in Dymola.

Output
^^^^^^

The main output from running ``CYMDISTToFMU.py`` consists of an FMU, named after the ``modelName`` specified in the input file.
The FMU is written to the current working directory, that is, in the directory from which you entered the command.

The FMU is complete and self-contained.
Any secondary output from running the CYMDISTToFMU tools can be deleted safely.

Note that the FMU is a zip file.
This means you can open and inspect its contents.
To do so, it may help to change the "``.fmu``" extension to "``.zip``".
