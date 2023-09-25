/*
 This file contains a CreateWindow function which sets up the OpenGL context.
 The goal is to reduce the size of the main.c file and clean up everything.
*/

int CreateWindow(int width,int height)
{

  /* start GL context and O/S window using the GLFW helper library */
  if ( !glfwInit() ) {
    fprintf( stderr, "ERROR: could not start GLFW3\n" );
    return 1;
  }

  /* Version 4.1 Core is a good default that should run on just about everything. Adjust later to suit project requirements. */
  glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
  glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
  glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
  glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

  window = glfwCreateWindow( width, height, "Chastity Checkerboard", NULL, NULL );
  if ( !window ) {
    fprintf( stderr, "ERROR: could not open window with GLFW3\n" );
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent( window );

  /* start GLEW extension handler */
  glewExperimental = GL_TRUE;
  glewInit();

  /* get version info */
  renderer = glGetString( GL_RENDERER ); /* get renderer string */
  version  = glGetString( GL_VERSION );  /* version as a string */
  printf( "Renderer: %s\n", renderer );
  printf( "OpenGL version supported %s\n", version );

  /* tell GL to only draw onto a pixel if the shape is closer to the viewer
  than anything already drawn at that pixel */
  glEnable( GL_DEPTH_TEST ); /* enable depth-testing */
  /* with LESS depth-testing interprets a smaller depth value as meaning "closer" */
  glDepthFunc( GL_LESS );

  glGenBuffers( 1, &points_vbo );
  glBindBuffer( GL_ARRAY_BUFFER, points_vbo );
  glBufferData( GL_ARRAY_BUFFER, 18 * sizeof( GLfloat ), points, GL_STATIC_DRAW );

  /* create a second VBO, containing the array of colours.
  note that we could also put them both into a single vertex buffer. in this
  case we would use the pointer and stride parameters of glVertexAttribPointer()
  to describe the different data layouts */

  glGenBuffers( 1, &colours_vbo );
  glBindBuffer( GL_ARRAY_BUFFER, colours_vbo );
  glBufferData( GL_ARRAY_BUFFER, 18 * sizeof( GLfloat ), colours, GL_STATIC_DRAW );




  /* create the VAO.
  we bind each VBO in turn, and call glVertexAttribPointer() to indicate where
  the memory should be fetched for vertex shader input variables 0, and 1,
  respectively. we also have to explicitly enable both 'attribute' variables.
  'attribute' is the older name for vertex shader 'in' variables. */


  glGenVertexArrays( 1, &vao );
  glBindVertexArray( vao );
  glBindBuffer( GL_ARRAY_BUFFER, points_vbo );
  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );
  glBindBuffer( GL_ARRAY_BUFFER, colours_vbo );
  glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, NULL );
  glEnableVertexAttribArray( 0 );
  glEnableVertexAttribArray( 1 );

  /* here we copy the shader strings into GL shaders, and compile them. we
  then create an executable shader 'program' and attach both of the compiled
      shaders. we link this, which matches the outputs of the vertex shader to
  the inputs of the fragment shader, etc. and it is then ready to use */
  vert_shader = glCreateShader( GL_VERTEX_SHADER );
  glShaderSource( vert_shader, 1, &vertex_shader, NULL );
  glCompileShader( vert_shader );
  frag_shader = glCreateShader( GL_FRAGMENT_SHADER );
  glShaderSource( frag_shader, 1, &fragment_shader, NULL );
  glCompileShader( frag_shader );
  shader_programme = glCreateProgram();
  glAttachShader( shader_programme, frag_shader );
  glAttachShader( shader_programme, vert_shader );
  glLinkProgram( shader_programme );

  glUseProgram( shader_programme );

  /*glClearColor(0.5,0.5,0.5,1.0);*/


 return 0;
}
