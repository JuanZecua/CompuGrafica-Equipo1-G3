/*
* Proyecto final Computacion grafica 
* Alumnos: 
*		   Zecua Salinas Juan Carlos 
* 
*/

#include <iostream>
#include <stdlib.h>

// GLAD: Multi-Language GL/GLES/EGL/GLX/WGL Loader-Generator
// https://glad.dav1d.de/
#include <glad/glad.h>

// GLFW: https://www.glfw.org/
#include <GLFW/glfw3.h>

// GLM: OpenGL Math library
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Model loading classes
#include <shader_m.h>
#include <camera.h>
#include <model.h>
#include <material.h>
#include <light.h>
#include <cubemap.h>

#include <irrKlang.h>
using namespace irrklang;

// Max number of bones
#define MAX_RIGGING_BONES 100
#define MAX_RIGGING_BONESS 100
#define MAX_RIGGING_BONESSS 100
#define MAX_RIGGING_BONESSSS 100
#define MAX_RIGGING_BONESSSSS 100

// Functions
bool Start();
bool Update();

// Definición de callbacks
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// Gobals
GLFWwindow* window;

// Tamaño en pixeles de la ventana
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;

// Definición de cámara (posición en XYZ)
Camera camera(glm::vec3(0.0f, 2.0f, 10.0f));
Camera camera3rd(glm::vec3(1.0f, 1.0f, 1.0f));

// Controladores para el movimiento del mouse
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// Variables para la velocidad de reproducción
// de la animación
float deltaTime = 0.0f;
float lastFrame = 0.0f;
float elapsedTime = 0.0f;

float deltaTime2 = 0.0f;
float lastFrame2 = 0.0f;
float elapsedTime2 = 0.0f;

float deltaTime3 = 0.0f;
float lastFrame3 = 0.0f;
float elapsedTime3 = 0.0f;

float deltaTime4 = 0.0f;
float lastFrame4 = 0.0f;
float elapsedTime4 = 0.0f;

float deltaTime5 = 0.0f;
float lastFrame5 = 0.0f;
float elapsedTime5 = 0.0f;

float sineTime = 0.0f;

glm::vec3 position(0.0f,0.0f, 0.0f);
glm::vec3 forwardView(0.0f, 0.0f, 1.0f);
float     scaleV = 0.005f;
float     rotateCharacter = 0.0f;
float     rotatepinguino1 = 0.0f;
float     rotatehipo2 = 0.0f;
float	  rotateelefantehuesos2 = 0.0f;
float     rotateTable = 0.0f;
glm::vec3 positionTable(0.0f, 0.0f, 0.0f);

// Shaders
Shader *ourShader;
Shader *staticShader;
Shader *phongShader;
Shader *fresnelShader;
Shader *cubemapShader;

// Carga la información del modelo
Model	*character;
Model	*house;
Model	*table;
Model   *sphere;
Model* pinguino1;
Model* hipo2;
Model* elefantehuesos2;
Model* zool1;
Model* pingu;
Model* leon;
Model* tick;
Model* carito2;
Model* mesa1;
Model* mesa2;
Model* mesa3;
Model* dog;
Model* cangu;
Model* fuente;
Model* tigre2;
Model* coco;


float tradius = 10.0f;
float theta = 0.0f;
float alpha = 0.0f;

// Cubemap
CubeMap *mainCubeMap;

// Materiales
Material material01;
Light    light01;
Light    light02;

// Pose inicial del modelo
glm::mat4 gBones[MAX_RIGGING_BONES];
glm::mat4 gBonesBar[MAX_RIGGING_BONES];

float	fps = 0.0f;
int		keys = 0;
int		animationCount = 0;


glm::mat4 gBones2[MAX_RIGGING_BONESS];
glm::mat4 gBonesBar2[MAX_RIGGING_BONESS];

float	fps2 = 0.0f;
int		keys2 = 0;
int		animationCount2 = 0;

glm::mat4 gBones3[MAX_RIGGING_BONESSS];
glm::mat4 gBonesBar3[MAX_RIGGING_BONESSS];

float	fps3 = 0.0f;
int		keys3 = 0;
int		animationCount3 = 0;

glm::mat4 gBones4[MAX_RIGGING_BONESSSS];
glm::mat4 gBonesBar4[MAX_RIGGING_BONESSSS];

float	fps4 = 0.0f;
int		keys4 = 0;
int		animationCount4 = 0;

glm::mat4 gBones5[MAX_RIGGING_BONESSSSS];
glm::mat4 gBonesBar5[MAX_RIGGING_BONESSSSS];

float	fps5 = 0.0f;
int		keys5 = 0;
int		animationCount5 = 0;

// Audio
ISoundEngine *SoundEngine = createIrrKlangDevice();

// selección de cámara
bool    activeCamera = 1; // activamos la primera cámara

// Entrada a función principal
int main()
{
	if (!Start())
		return -1;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		if (!Update())
			break;
	}

	glfwTerminate();
	return 0;

}

bool Start() {
	// Inicialización de GLFW

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creación de la ventana con GLFW
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "FBX Animation with OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Ocultar el cursor mientras se rota la escena
	// glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: Cargar todos los apuntadores
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	// Activación de buffer de profundidad
	glEnable(GL_DEPTH_TEST);

	// Compilación y enlace de shaders
	ourShader     = new Shader("shaders/10_vertex_skinning-IT.vs", "shaders/10_fragment_skinning-IT.fs");
	staticShader  = new Shader("shaders/10_vertex_simple.vs", "shaders/10_fragment_simple.fs");
	phongShader   = new Shader("shaders/11_BasicPhongShader.vs", "shaders/11_BasicPhongShader.fs");
	fresnelShader = new Shader("shaders/11_Fresnel.vs", "shaders/11_Fresnel.fs");
	cubemapShader = new Shader("shaders/10_vertex_cubemap.vs", "shaders/10_fragment_cubemap.fs");

	// Máximo número de huesos: 100
	ourShader->setBonesIDs(MAX_RIGGING_BONES);

	// Dibujar en malla de alambre
	// glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

	house = new Model("models/IllumModels/House02.fbx");
	table = new Model("models/IllumModels/Table02.fbx");
	character = new Model("models/IllumModels/KAYA.fbx");
	sphere = new Model("models/IllumModels/Sphere.fbx");
	pinguino1 = new Model("models/pinguino1.fbx");
	hipo2 = new Model("models/hipo2.fbx");
	elefantehuesos2 = new Model("models/elefantehuesos2.fbx");
	pingu = new Model("models/pingu.fbx");
	zool1 = new Model("models/zool1.fbx");
	leon = new Model("models/leon.fbx");
	tick = new Model("models/tick.fbx");
	carito2 = new Model("models/carito2.fbx");
	mesa1 = new Model("models/mesa1.fbx");
	mesa2 = new Model("models/mesa2.fbx");
	mesa3 = new Model("models/mesa3.fbx");
	dog = new Model("models/dog.fbx");
	cangu = new Model("models/cangu.fbx");
	fuente = new Model("models/fuente.fbx");
	tigre2 = new Model("models/tigre2.fbx");
	coco = new Model("models/coco.fbx");

	// Cubemap
	vector<std::string> faces
	{
		"textures/cubemap/01/posx.png",
		"textures/cubemap/01/negx.png",
		"textures/cubemap/01/posy.png",
		"textures/cubemap/01/negy.png",
		"textures/cubemap/01/posz.png",
		"textures/cubemap/01/negz.png"
	};
	mainCubeMap = new CubeMap();
	mainCubeMap->loadCubemap(faces);
	
	// time, arrays
	character->SetPose(0.0f, gBones);

	fps = (float)character->getFramerate();
	keys = (int)character->getNumFrames();

	hipo2->SetPose(0.0f, gBones2);

	fps2 = (float)hipo2->getFramerate();
	keys2 = (int)hipo2->getNumFrames();

	elefantehuesos2->SetPose(0.0f, gBones5);

	fps5 = (float)elefantehuesos2->getFramerate();
	keys5 = (int)elefantehuesos2->getNumFrames();

	pingu->SetPose(0.0f, gBones3);

	fps3 = (float)pingu->getFramerate();
	keys3 = (int)pingu->getNumFrames();

	leon->SetPose(0.0f, gBones4);

	fps4 = (float)leon->getFramerate();
	keys4 = (int)leon->getNumFrames();


	camera3rd.Position = position;
	camera3rd.Position.y += 1.7f;
	camera3rd.Position -= forwardView;
	camera3rd.Front = forwardView;

	// SoundEngine->play2D("sound/EternalGarden.mp3", true);

	return true;
}

bool Update() {
	// Cálculo del framerate
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	elapsedTime += deltaTime;
	if (elapsedTime > 1.0f / fps) {
		animationCount++;
		if (animationCount > keys - 1) {
			animationCount = 0;
		}
		// Configuración de la pose en el instante t
		character->SetPose((float)animationCount, gBones);
		//pinguino1->SetPose((float)animationCount, gBones);
		//hipo2->SetPose((float)animationCount, gBones);
		//elefantehuesos2->SetPose((float)animationCount, gBones);
		elapsedTime = 0.0f;

	}

	float currentFrame2 = (float)glfwGetTime();
	deltaTime2 = currentFrame2 - lastFrame2;
	lastFrame2 = currentFrame2;

	elapsedTime2 += deltaTime2;
	if (elapsedTime2 > 1.0f / fps2) {
		animationCount2++;
		if (animationCount2 > keys2 - 1) {
			animationCount2 = 0;
		}
		// Configuración de la pose en el instante t
		//character->SetPose((float)animationCount, gBones);
		//pinguino1->SetPose((float)animationCount, gBones);
		hipo2->SetPose((float)animationCount2, gBones2);
		//elefantehuesos2->SetPose((float)animationCount, gBones);
		elapsedTime2 = 0.0f;

	}

	float currentFrame3 = (float)glfwGetTime();
	deltaTime3 = currentFrame3 - lastFrame3;
	lastFrame3 = currentFrame3;

	elapsedTime3 += deltaTime3;
	if (elapsedTime3 > 1.0f / fps3) {
		animationCount3++;
		if (animationCount3 > keys3 - 1) {
			animationCount3 = 0;
		}
		// Configuración de la pose en el instante t
		//character->SetPose((float)animationCount, gBones);
		//pinguino1->SetPose((float)animationCount, gBones);
		pingu->SetPose((float)animationCount3, gBones3);
		//elefantehuesos2->SetPose((float)animationCount, gBones);
		elapsedTime3 = 0.0f;

	}

	float currentFrame4 = (float)glfwGetTime();
	deltaTime4 = currentFrame4 - lastFrame4;
	lastFrame4 = currentFrame4;

	elapsedTime4 += deltaTime4;
	if (elapsedTime4 > 1.0f / fps4) {
		animationCount4++;
		if (animationCount4 > keys4 - 1) {
			animationCount4 = 0;
		}
		// Configuración de la pose en el instante t
		//character->SetPose((float)animationCount, gBones);
		//pinguino1->SetPose((float)animationCount, gBones);
		leon->SetPose((float)animationCount4, gBones4);
		//elefantehuesos2->SetPose((float)animationCount, gBones);
		elapsedTime4 = 0.0f;

	}

	float currentFrame5 = (float)glfwGetTime();
	deltaTime5 = currentFrame5 - lastFrame5;
	lastFrame5 = currentFrame5;

	elapsedTime5 += deltaTime5;
	if (elapsedTime5 > 1.0f / fps5) {
		animationCount5++;
		if (animationCount5 > keys5 - 1) {
			animationCount5 = 0;
		}
		// Configuración de la pose en el instante t
		//character->SetPose((float)animationCount, gBones);
		//pinguino1->SetPose((float)animationCount, gBones);
		//hipo2->SetPose((float)animationCount, gBones);
		elefantehuesos2->SetPose((float)animationCount5, gBones5);
		elapsedTime5 = 0.0f;

	}
	// Procesa la entrada del teclado o mouse
	processInput(window);

	// Renderizado R - G - B - A
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Cubemap (fondo)
	{
		glm::mat4 projection;
		glm::mat4 view;

		if (activeCamera) {
			projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
			view = camera.GetViewMatrix();
		}
		else {
			projection = glm::perspective(glm::radians(camera3rd.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
			view = camera3rd.GetViewMatrix();
		}
		
		mainCubeMap->drawCubeMap(*cubemapShader, projection, view);
	}

	
	
	// Objeto estático (zoologico)
	 {
		// Activamos el shader del plano
		staticShader->use();

		// Activamos para objetos transparentes
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glm::mat4 projection;
		glm::mat4 view;

		if (activeCamera) {
			projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
			view = camera.GetViewMatrix();
		}
		else {
			projection = glm::perspective(glm::radians(camera3rd.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
			view = camera3rd.GetViewMatrix();
		}
		
		staticShader->setMat4("projection", projection);
		staticShader->setMat4("view", view);

		// Aplicamos transformaciones del modelo
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(50.0f, 50.0f, 50.0f));	// it's a bit too big for our scene, so scale it down
		staticShader->setMat4("model", model);

		zool1->Draw(*staticShader);
	}

	 // Objeto estático (tickets)
	 {
		 // Activamos el shader del plano
		 staticShader->use();

		 // Activamos para objetos transparentes
		 glEnable(GL_BLEND);
		 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		 glm::mat4 projection;
		 glm::mat4 view;

		 if (activeCamera) {
			 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			 view = camera.GetViewMatrix();
		 }
		 else {
			 projection = glm::perspective(glm::radians(camera3rd.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
			 view = camera3rd.GetViewMatrix();
		 }

		 staticShader->setMat4("projection", projection);
		 staticShader->setMat4("view", view);

		 // Aplicamos transformaciones del modelo
		 glm::mat4 model = glm::mat4(1.0f);
		 model = glm::translate(model, glm::vec3(37, 0, -23)); // translate it down so it's at the center of the scene
		 model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(1.0f, 0.0f, 0));
		 model = glm::scale(model, glm::vec3(0.02,0.02,0.02));	// it's a bit too big for our scene, so scale it down
		 staticShader->setMat4("model", model);

		 tick->Draw(*staticShader);
	 }

	glUseProgram(0); 

	// se dibuja el tigre
	{
		// Activamos el shader del plano
		staticShader->use();

		// Activamos para objetos transparentes
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glm::mat4 projection;
		glm::mat4 view;

		if (activeCamera) {
			projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			view = camera.GetViewMatrix();
		}
		else {
			projection = glm::perspective(glm::radians(camera3rd.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
			view = camera3rd.GetViewMatrix();
		}

		staticShader->setMat4("projection", projection);
		staticShader->setMat4("view", view);

		// Aplicamos transformaciones del modelo
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(3, 0 , -36)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0));
		model = glm::scale(model, glm::vec3(0.02, 0.02, 0.02));	// it's a bit too big for our scene, so scale it down
		staticShader->setMat4("model", model);

		tigre2->Draw(*staticShader);
	}

	glUseProgram(0);

	{
		// Activamos el shader del plano
		staticShader->use();

		// Activamos para objetos transparentes
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glm::mat4 projection;
		glm::mat4 view;

		if (activeCamera) {
			projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			view = camera.GetViewMatrix();
		}
		else {
			projection = glm::perspective(glm::radians(camera3rd.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
			view = camera3rd.GetViewMatrix();
		}

		staticShader->setMat4("projection", projection);
		staticShader->setMat4("view", view);

		// Aplicamos transformaciones del modelo
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(35, 0, -25)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0));
		model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0));	// it's a bit too big for our scene, so scale it down
		staticShader->setMat4("model", model);

		coco->Draw(*staticShader);
	}

	glUseProgram(0);

	//se dibuja un perro

	{
		// Activamos el shader del plano
		staticShader->use();

		// Activamos para objetos transparentes
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glm::mat4 projection;
		glm::mat4 view;

		if (activeCamera) {
			projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			view = camera.GetViewMatrix();
		}
		else {
			projection = glm::perspective(glm::radians(camera3rd.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
			view = camera3rd.GetViewMatrix();
		}

		staticShader->setMat4("projection", projection);
		staticShader->setMat4("view", view);

		// Aplicamos transformaciones del modelo
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0, 2, 0)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0));
		model = glm::scale(model, glm::vec3(0.02, 0.02, 0.02));	// it's a bit too big for our scene, so scale it down
		staticShader->setMat4("model", model);

		dog->Draw(*staticShader);
	}

	glUseProgram(0);

	// se dibuja la fuente
	{
		// Activamos el shader del plano
		staticShader->use();

		// Activamos para objetos transparentes
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glm::mat4 projection;
		glm::mat4 view;

		if (activeCamera) {
			projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			view = camera.GetViewMatrix();
		}
		else {
			projection = glm::perspective(glm::radians(camera3rd.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
			view = camera3rd.GetViewMatrix();
		}

		staticShader->setMat4("projection", projection);
		staticShader->setMat4("view", view);

		// Aplicamos transformaciones del modelo
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0,-1,0)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0));
		model = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));	// it's a bit too big for our scene, so scale it down
		staticShader->setMat4("model", model);

		fuente->Draw(*staticShader);
	}

	glUseProgram(0);

	{
		// Activamos el shader del plano
		staticShader->use();

		// Activamos para objetos transparentes
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glm::mat4 projection;
		glm::mat4 view;

		if (activeCamera) {
			projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			view = camera.GetViewMatrix();
		}
		else {
			projection = glm::perspective(glm::radians(camera3rd.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
			view = camera3rd.GetViewMatrix();
		}

		staticShader->setMat4("projection", projection);
		staticShader->setMat4("view", view);

		// Aplicamos transformaciones del modelo
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-22, 0, 28)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0));
		model = glm::scale(model, glm::vec3(0.02, 0.025, 0.02));	// it's a bit too big for our scene, so scale it down
		staticShader->setMat4("model", model);

		cangu->Draw(*staticShader);
	}

	glUseProgram(0);

	// Objeto estático (carrito hot-dog)
	{
		// Activamos el shader del plano
		staticShader->use();

		// Activamos para objetos transparentes
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glm::mat4 projection;
		glm::mat4 view;

		if (activeCamera) {
			projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			view = camera.GetViewMatrix();
		}
		else {
			projection = glm::perspective(glm::radians(camera3rd.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
			view = camera3rd.GetViewMatrix();
		}

		staticShader->setMat4("projection", projection);
		staticShader->setMat4("view", view);

		// Aplicamos transformaciones del modelo
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(15, 1,0)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(-90, 0,0));
		model = glm::scale(model, glm::vec3(3.0, 3.0, 3.0));	// it's a bit too big for our scene, so scale it down
		staticShader->setMat4("model", model);

		carito2->Draw(*staticShader);
	}

	glUseProgram(0);

	// Objeto estático (mesa1)
	{
		// Activamos el shader del plano
		staticShader->use();

		// Activamos para objetos transparentes
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glm::mat4 projection;
		glm::mat4 view;

		if (activeCamera) {
			projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			view = camera.GetViewMatrix();
		}
		else {
			projection = glm::perspective(glm::radians(camera3rd.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
			view = camera3rd.GetViewMatrix();
		}

		staticShader->setMat4("projection", projection);
		staticShader->setMat4("view", view);

		// Aplicamos transformaciones del modelo
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-35, 1, 35)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0));
		model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));	// it's a bit too big for our scene, so scale it down
		staticShader->setMat4("model", model);

		mesa1->Draw(*staticShader);
	}

	glUseProgram(0);

	{
		// Activamos el shader del plano
		staticShader->use();

		// Activamos para objetos transparentes
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glm::mat4 projection;
		glm::mat4 view;

		if (activeCamera) {
			projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			view = camera.GetViewMatrix();
		}
		else {
			projection = glm::perspective(glm::radians(camera3rd.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
			view = camera3rd.GetViewMatrix();
		}

		staticShader->setMat4("projection", projection);
		staticShader->setMat4("view", view);

		// Aplicamos transformaciones del modelo
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-30, 1, 35)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0));
		model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));	// it's a bit too big for our scene, so scale it down
		staticShader->setMat4("model", model);

		mesa1->Draw(*staticShader);
	}

	glUseProgram(0);

	{
		// Activamos el shader del plano
		staticShader->use();

		// Activamos para objetos transparentes
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glm::mat4 projection;
		glm::mat4 view;

		if (activeCamera) {
			projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			view = camera.GetViewMatrix();
		}
		else {
			projection = glm::perspective(glm::radians(camera3rd.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
			view = camera3rd.GetViewMatrix();
		}

		staticShader->setMat4("projection", projection);
		staticShader->setMat4("view", view);

		// Aplicamos transformaciones del modelo
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-37, 1, 0)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0));
		model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));	// it's a bit too big for our scene, so scale it down
		staticShader->setMat4("model", model);

		mesa2->Draw(*staticShader);
	}

	glUseProgram(0);

	{
		// Activamos el shader del plano
		staticShader->use();

		// Activamos para objetos transparentes
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glm::mat4 projection;
		glm::mat4 view;

		if (activeCamera) {
			projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			view = camera.GetViewMatrix();
		}
		else {
			projection = glm::perspective(glm::radians(camera3rd.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
			view = camera3rd.GetViewMatrix();
		}

		staticShader->setMat4("projection", projection);
		staticShader->setMat4("view", view);

		// Aplicamos transformaciones del modelo
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-37, 1, -23)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0));
		model = glm::scale(model, glm::vec3(0.1, 0.1, 0.1));	// it's a bit too big for our scene, so scale it down
		staticShader->setMat4("model", model);

		mesa3->Draw(*staticShader);
	}

	glUseProgram(0);
	
	{
		// Activación del shader del personaje
		ourShader->use();

		// Aplicamos transformaciones de proyección y cámara (si las hubiera)

		glm::mat4 projection;
		glm::mat4 view;

		if (activeCamera) {
			projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.5f, 10000.0f);
			view = camera.GetViewMatrix();
		}
		else {
			projection = glm::perspective(glm::radians(camera3rd.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
			view = camera3rd.GetViewMatrix();
		}

		ourShader->setMat4("projection", projection);
		ourShader->setMat4("view", view);

		// Aplicamos transformaciones del modelo
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, position); // translate it down so it's at the center of the scene
		model = glm::rotate(model, glm::radians(rotateCharacter), glm::vec3(0.0, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));	// it's a bit too big for our scene, so scale it down

		ourShader->setMat4("model", model);

		ourShader->setMat4("gBones", MAX_RIGGING_BONES, gBones);

		// Dibujamos el modelo
		character->Draw(*ourShader);
	}

	glUseProgram(0);
	// pinguino
	{
		// Activación del shader del personaje
		ourShader->use();

		// Aplicamos transformaciones de proyección y cámara (si las hubiera)
		
		glm::mat4 projection;
		glm::mat4 view;

		if (activeCamera) {
			projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.5f, 10000.0f);
			view = camera.GetViewMatrix();
		}
		else {
			projection = glm::perspective(glm::radians(camera3rd.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
			view = camera3rd.GetViewMatrix();
		}
		
		ourShader->setMat4("projection", projection);
		ourShader->setMat4("view", view);

		// Aplicamos transformaciones del modelo
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(25, 0, 35)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));	// it's a bit too big for our scene, so scale it down

		ourShader->setMat4("model", model);

		ourShader->setMat4("gBones", MAX_RIGGING_BONESSS, gBones3);

		// Dibujamos el modelo
		pingu->Draw(*ourShader);
	}

	glUseProgram(0); 

	// leon
	{
		// Activación del shader del personaje
		ourShader->use();

		// Aplicamos transformaciones de proyección y cámara (si las hubiera)

		glm::mat4 projection;
		glm::mat4 view;

		if (activeCamera) {
			projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.5f, 10000.0f);
			view = camera.GetViewMatrix();
		}
		else {
			projection = glm::perspective(glm::radians(camera3rd.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
			view = camera3rd.GetViewMatrix();
		}

		ourShader->setMat4("projection", projection);
		ourShader->setMat4("view", view);

		// Aplicamos transformaciones del modelo
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-22, 2, -23)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));	// it's a bit too big for our scene, so scale it down

		ourShader->setMat4("model", model);

		ourShader->setMat4("gBones", MAX_RIGGING_BONESSSS, gBones4);

		// Dibujamos el modelo
		leon->Draw(*ourShader);
	}

	glUseProgram(0);

	// hipopotamo
	{
		// Activación del shader del personaje
		ourShader->use();

		// Aplicamos transformaciones de proyección y cámara (si las hubiera)

		glm::mat4 projection;
		glm::mat4 view;

		if (activeCamera) {
			projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.5f, 10000.0f);
			view = camera.GetViewMatrix();
		}
		else {
			projection = glm::perspective(glm::radians(camera3rd.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
			view = camera3rd.GetViewMatrix();
		}

		ourShader->setMat4("projection", projection);
		ourShader->setMat4("view", view);

		// Aplicamos transformaciones del modelo
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(3, 2, 38)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.005f, 0.005f, 0.005f));	// it's a bit too big for our scene, so scale it down

		ourShader->setMat4("model", model);

		ourShader->setMat4("gBones", MAX_RIGGING_BONESS, gBones2);

		// Dibujamos el modelo
		hipo2->Draw(*ourShader);
	}

	glUseProgram(0);

	// Objeto animado elefante
	{
		// Activación del shader del personaje
		ourShader->use();

		// Aplicamos transformaciones de proyección y cámara (si las hubiera)

		glm::mat4 projection;
		glm::mat4 view;

		if (activeCamera) {
			projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.6f, 10000.0f);
			view = camera.GetViewMatrix();
		}
		else {
			projection = glm::perspective(glm::radians(camera3rd.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.2f, 10000.0f);
			view = camera3rd.GetViewMatrix();
		}

		ourShader->setMat4("projection", projection);
		ourShader->setMat4("view", view);

		// Aplicamos transformaciones del modelo
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-24, 2.3, -2)); // translate it down so it's at the center of the scene
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));	// it's a bit too big for our scene, so scale it down

		ourShader->setMat4("model", model);

		ourShader->setMat4("gBones", MAX_RIGGING_BONESSSSS, gBones5);

		// Dibujamos el modelo
		elefantehuesos2->Draw(*ourShader);
	}

	glUseProgram(0);
	
	{
		// Activamos el shader de Phong
		phongShader->use();

		// Activamos para objetos transparentes
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Aplicamos transformaciones de proyección y cámara (si las hubiera)
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		phongShader->setMat4("projection", projection);
		phongShader->setMat4("view", view);

		// Aplicamos transformaciones del modelo
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotateTable), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		phongShader->setMat4("model", model);

		// Configuramos propiedades de fuentes de luz
		phongShader->setVec4("LightColor", light01.Color);
		phongShader->setVec4("LightPower", light01.Power);
		phongShader->setInt("alphaIndex", light01.alphaIndex);
		phongShader->setFloat("distance", light01.distance);
		phongShader->setVec3("lightPosition", light01.Position);
		phongShader->setVec3("lightDirection", light01.Direction);
		phongShader->setVec3("eye", camera.Position);

		// Aplicamos propiedades materiales
		phongShader->setVec4("MaterialAmbientColor", material01.ambient);
		phongShader->setVec4("MaterialDiffuseColor", material01.diffuse);
		phongShader->setVec4("MaterialSpecularColor", material01.specular);
		phongShader->setFloat("transparency", material01.transparency);

		//sphere->Draw(*phongShader);

	}

	glUseProgram(0);



	/*
	// Dibujamos una mesa
	{
		// Activamos el shader de fresnel
		fresnelShader->use();

		// Activamos para objetos transparentes
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Aplicamos transformaciones de proyección y cámara (si las hubiera)
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		fresnelShader->setMat4("projection", projection);
		fresnelShader->setMat4("view", view);

		// Aplicamos transformaciones del modelo
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, positionTable);
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotateTable), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		fresnelShader->setMat4("model", model);
		fresnelShader->setFloat("time", sineTime);
		sineTime += 0.001;
		fresnelShader->setFloat("transparency", 1.0f);

		glDepthMask(GL_FALSE);
		glBindTexture(GL_TEXTURE_CUBE_MAP, mainCubeMap->textureID);
		glDepthMask(GL_TRUE);
		table->Draw(*fresnelShader);

	}

	glUseProgram(0); */

	// glfw: swap buffers 
	glfwSwapBuffers(window);
	glfwPollEvents();

	return true;
}

// Procesamos entradas del teclado
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

	// Character movement
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {

		position = position + scaleV * forwardView;
		camera3rd.Front = forwardView;
		camera3rd.ProcessKeyboard(FORWARD, deltaTime);
		camera3rd.Position = position;
		camera3rd.Position.y += 1.7f;
		camera3rd.Position -= forwardView;

	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		position = position - scaleV * forwardView;
		camera3rd.Front = forwardView;
		camera3rd.ProcessKeyboard(BACKWARD, deltaTime);
		camera3rd.Position = position;
		camera3rd.Position.y += 1.7f;
		camera3rd.Position -= forwardView;
	}
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
		
	}
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
		
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
		positionTable.x -= 0.01;
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		positionTable.x += 0.01;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		rotateCharacter += 0.5f;

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(rotateCharacter), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::vec4 viewVector = model * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
		forwardView = glm::vec3(viewVector);
		forwardView = glm::normalize(forwardView);

		camera3rd.Front = forwardView;
		camera3rd.Position = position;
		camera3rd.Position.y += 2.0f;
		camera3rd.Position -= forwardView;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		rotateCharacter -= 0.5f;

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(rotateCharacter), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::vec4 viewVector = model * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
		forwardView = glm::vec3(viewVector);
		forwardView = glm::normalize(forwardView);

		camera3rd.Front = forwardView;
		camera3rd.Position = position;
		camera3rd.Position.y += 2.0f;
		camera3rd.Position -= forwardView;
	}

	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
	{
		rotateTable += 0.05f;
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
	{
		rotateTable -= 0.05f;
	}
	
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		light01.Position.x += 0.1;
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
		light01.Position.x -= 0.1;
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		light01.Position.y += 0.1;
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		light01.Position.y -= 0.1;

	if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS)
		activeCamera = 0;
	if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
		activeCamera = 2;
	
}

// glfw: Actualizamos el puerto de vista si hay cambios del tamaño
// de la ventana
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// glfw: Callback del movimiento y eventos del mouse
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	float xoffset = (float)xpos - lastX;
	float yoffset = lastY - (float)ypos; 

	lastX = (float)xpos;
	lastY = (float)ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: Complemento para el movimiento y eventos del mouse
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll((float)yoffset);
}
