#shader vertex
#version 330 core
     layout (location = 0) in vec2 aPos;   
     layout (location = 1) in vec2 texCoord; 
     layout (location = 2) in vec2 aOffset; 
     out vec2 v_TexCoord; 
     uniform mat4 u_MVP;
     void main()   
     {   
        vec2 pos = aPos + aOffset; 
        //gl_Position= aPos; 
        gl_Position = u_MVP * vec4(pos, -1.0f, 1.0f); 
        //gl_Position = vec4(pos, 0.0, 1.0); 
        v_TexCoord = texCoord; 
     };

#shader fragment
#version 330 core  
     layout (location = 0) out vec4 FragColor;
     in vec2 v_TexCoord;
     //uniform vec4 u_Color;
     uniform sampler2D u_Texture;   
     void main()   
     {   
          vec4 texColor = texture(u_Texture, v_TexCoord);
          //vec4 texColor = u_Color;
          FragColor = texColor;   
     };