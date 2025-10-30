# Proyecto: El Encanto ("Kuali")

## 1. Resumen Rápido
* **Objetivo:** Desarrollar una plataforma de gestión integral ("Kuali") para el bioparque "El Encanto", empezando con un MVP enfocado en el Módulo Educativo (reservas de grupos), seguido por módulos como Veterinaria e integraciones IoT. El sistema busca modernizar operaciones, automatizar procesos y centralizar información.
* **Estado Actual:** Listo para iniciar el desarrollo del PoC (Prueba de Concepto) del Módulo Educativo.
* **Próxima Tarea:** (Desde GitHub Projects) - Tarea #1: Configurar proyecto Django y base de datos SQLite.

---
## 2. Stack Tecnológico (Índice)
*Aquí está el stack actual. Haz clic en cualquier elemento para ver el "porqué" lo elegimos.*

* **Backend Principal:** [Django](#django-contexto) (con [DRF](#drf-contexto) y [Wagtail](#wagtail-contexto))
* **Backend Específico:** [FastAPI](#fastapi-contexto)
* **Frontend Apps Internas:** [Flet](#flet-contexto) (con [Flet Studio](#flet-contexto) y [Flet View](#flet-contexto))
* **Base de Datos:** [Cloud SQL (PostgreSQL)](#bd-contexto)
* **Infraestructura:** [Google Cloud Platform (GCP)](#gcp-contexto) (con [Cloud Run](#gcp-contexto) y [Terraform](#terraform-contexto))
* **Servicios Externos:** [Firebase](#firebase-contexto) (Auth y Realtime DB), [Twilio](#comunicaciones-contexto) (o similar)
* **Desarrollo y Pruebas:** [Pytest](#pytest-contexto), [Google Colab](#colab-contexto), [Git](#git-contexto), [GitHub](#github-contexto) (con [Projects](#github-contexto) & [Wiki](#github-contexto))

---
## 3. Contexto y Razonamiento del Stack
*Esta sección es nuestra "memoria" de las decisiones clave.*

### <a name="django-contexto"></a>Django (con DRF y Wagtail)
* **¿Qué es?:** Nuestro framework de backend principal (Python).
* **Nuestra Conclusión (El Porqué):** Se eligió Django por su filosofía de "baterías incluidas". Su **Panel de Administración** autogenerado es la ventaja decisiva para acelerar la creación de herramientas internas (Veterinaria, CRM básico). Su ORM robusto es ideal para manejar la complejidad de datos relacionales del proyecto. Permite construir nuestro propio CRM a medida, lo cual es más potente y flexible que integrar uno externo para el corazón del negocio.

### <a name="drf-contexto"></a>Django REST Framework (DRF)
* **¿Qué es?:** Una librería que se añade a Django.
* **Nuestra Conclusión (El Porqué):** Esencial para convertir nuestro backend de Django en una API "headless" profesional. Permitirá la comunicación eficiente y segura entre Django y nuestro frontend de Flet.

### <a name="wagtail-contexto"></a>Wagtail CMS
* **¿Qué es?:** Un Sistema de Gestión de Contenido (CMS) que corre sobre Django.
* **Nuestra Conclusión (El Porqué):** Se integrará *dentro* de Django para gestionar el **sitio web público** (bioparc.com, blog, descripción de paquetes). Su interfaz amigable (incluyendo "Live Preview" y "StreamField") permitirá al personal no técnico (marketing, educación) actualizar contenido fácilmente sin tocar código, manteniendo el control del diseño en el desarrollador. Es superior a Django CMS para nuestro caso por dar más control estructural al desarrollador.

### <a name="fastapi-contexto"></a>FastAPI
* **¿Qué es?:** Otro framework de backend en Python.
* **Nuestra Conclusión (El Porqué):** Se usará **puntualmente** para crear microservicios o APIs específicas que requieran un rendimiento extremadamente alto (ej: procesamiento de pagos en el futuro, si Django se vuelve un cuello de botella), sin la carga completa de Django.

### <a name="flet-contexto"></a>Flet (con Flet Studio y Flet View)
* **¿Qué es?:** Nuestro framework de frontend (Python).
* **Nuestra Conclusión (El Porqué):** Permite construir la **interfaz de usuario de las aplicaciones internas y el portal de reservas** usando solo Python. Esto aprovecha tu fortaleza principal y evita JavaScript por ahora. Genera aplicaciones interactivas (SPA) para web y escritorio desde un solo código.
* **Herramientas Asociadas:**
    * **Flet Studio:** Se usará para el maquetado visual rápido ("drag-and-drop") y generar código base.
    * **Flet View (Hot Reload):** Se usará para el desarrollo diario con previsualización instantánea.

### <a name="bd-contexto"></a>Cloud SQL (PostgreSQL)
* **¿Qué es?:** Nuestra base de datos relacional gestionada en GCP.
* **Nuestra Conclusión (El Porqué):** Es el estándar profesional para Django. Google gestiona mantenimiento, backups y escalabilidad, permitiéndonos enfocarnos en la lógica de negocio. Es robusta para los datos complejos del proyecto.

### <a name="gcp-contexto"></a>Google Cloud Platform (GCP) (con Cloud Run)
* **¿Qué es?:** Nuestra plataforma de nube principal.
* **Nuestra Conclusión (El Porqué):** Aloja todos nuestros servicios (Cloud SQL, Cloud Run) de forma escalable y fiable. Ofrece las herramientas necesarias para desplegar y gestionar una aplicación profesional.
* **Componentes Clave:**
    * **Cloud Run:** Ejecutará nuestras aplicaciones Django y Flet en contenedores, escalando automáticamente.

### <a name="terraform-contexto"></a>Terraform
* **¿Qué es?:** Una herramienta de Infraestructura como Código (IaC).
* **Nuestra Conclusión (El Porqué):** Aunque no es para el PoC inicial, se usará a **largo plazo** para definir y gestionar toda la infraestructura de GCP (servidores, BDs, redes) mediante código. Esto permite automatización, control de versiones y replicación fácil de entornos (clave si se escala a otros departamentos o clientes).

### <a name="firebase-contexto"></a>Firebase (Servicios Complementarios)
* **¿Qué es?:** Un conjunto de servicios de Google (BaaS).
* **Nuestra Conclusión (El Porqué):** No se usará como backend principal. Se aprovecharán servicios específicos para acelerar el desarrollo:
    * **Firebase Authentication:** Simplifica y asegura el login del personal interno.
    * **Realtime Database / Firestore:** Para funcionalidades en tiempo real (notificaciones en dashboard, chat interno).

### <a name="comunicaciones-contexto"></a>Twilio (o similar)
* **¿Qué es?:** Un servicio externo para comunicaciones.
* **Nuestra Conclusión (El Porqué):** Se usará para automatizar el envío de emails y, potencialmente, SMS/WhatsApp para confirmaciones, recordatorios, etc.

### <a name="pytest-contexto"></a>Pytest
* **¿Qué es?:** El framework estándar para pruebas en Python.
* **Nuestra Conclusión (El Porqué):** Indispensable para el desarrollo profesional. Asegurará que la lógica del backend (Django) funcione correctamente y evitará regresiones.

### <a name="colab-contexto"></a>Google Colab
* **¿Qué es?:** Entorno de notebooks de Python en la nube.
* **Nuestra Conclusión (El Porqué):** Será nuestro "laboratorio de IA". Se usará específicamente para entrenar modelos de Machine Learning (ej: el "guardián inteligente", asignación de guías) usando GPUs gratuitas, separando esta experimentación del proyecto principal.

### <a name="git-contexto"></a>Git
* **¿Qué es?:** El sistema de control de versiones.
* **Nuestra Conclusión (El Porqué):** Fundamental. Registraremos cada cambio en el código. Se usará la estrategia de ramas **Git Flow simplificado** (main, develop, feature/...) para un desarrollo organizado y seguro.

### <a name="github-contexto"></a>GitHub (con Projects y Wiki)
* **¿Qué es?:** Nuestra plataforma central para alojar el código y gestionar el proyecto.
* **Nuestra Conclusión (El Porqué):** Centraliza todo:
    * **Repositorio:** Código fuente (gestionado con Git).
    * **GitHub Projects:** Gestión de tareas (tablero Kanban), integrado con Issues y código.
    * **GitHub Wiki:** Documentación estática del proyecto (ej: "Personas", guías de usuario).
    * **`README.md`:** Estado actual y stack (este archivo).
    * **`contexto_log.md`:** Historial de sesiones de trabajo.

---
---
## 4. Protocolo y Flujo de Trabajo (Guía Paso a Paso)
*Este es nuestro acuerdo "picado en piedra" sobre cómo gestionamos el proyecto y colaboramos.*

### A. Fuentes de Verdad (Dónde vive la información)
* **`README.md` (Este archivo):** El estado *actual* del proyecto, stack y este protocolo. Es nuestro "Dashboard".
* **`contexto_log.md`:** El *historial* de sesiones pasadas. Es nuestra "Bitácora de Vuelo".
* **`GitHub Issues`:** La lista de *todas* las tareas pendientes (bugs, features, etc.).
* **`GitHub Projects`:** El tablero visual (Kanban) que organiza los `Issues`.
* **`GitHub Wiki`:** La documentación *estática* del proyecto (Glosario, "Personas" de usuario, guías, etc).

### B. Configuración Inicial de Tareas (Qué hacer ANTES de empezar)
*Tú crearás las tareas (Issues) basándote en nuestro roadmap.*
1.  **Crear `Issue`:** Para cada nueva tarea (ej: "Modelar datos de Veterinaria"), crea un nuevo `Issue` en GitHub.
2.  **Asignar a `Projects`:** Ve a `GitHub Projects`, abre el tablero del proyecto, y arrastra el nuevo `Issue` a la columna **`Pendiente`**.

### C. Flujo de Trabajo por Sesión (La Guía del Día a Día)
*Esto es lo que hacemos cada vez que nos sentamos a trabajar.*

1.  **Inicio (Tu Lado):**
    * Vas a `GitHub Projects`.
    * Miras la columna **`Pendiente`** y eliges el `Issue` en el que trabajaremos (ej: `Issue #3`).
    * Arrastras la tarjeta del `Issue #3` a la columna **`En Progreso`**.
2.  **Carga de Contexto (Tu Lado):**
    * Vienes a este chat ("Discusiones Python").
    * Me pasas el contenido completo de `README.md` y las últimas entradas de `contexto_log.md`.
    * Me dices: "**Vamos a trabajar en el Issue #3: Modelar datos de Veterinaria**".
3.  **Creación de Rama (Tu Lado):**
    * Te sitúas en tu rama `develop`.
    * Creas una nueva rama de "feature" usando el número del Issue:
        `git checkout -b feature/3-modelado-veterinaria`
4.  **Desarrollo (Nuestro Lado):**
    * Trabajamos juntos en el código, siguiendo el objetivo del Issue.
    * Tú haces `commits` locales a tu rama `feature/...` tan a menudo como quieras.

### D. Flujo de Fin de Sesión (El Cierre)

5.  **Aviso de Cierre (Tu Lado):**
    * Me indicas que hemos terminado por hoy.
6.  **Generación de Textos (Mi Lado):**
    * Yo te entrego los siguientes bloques de texto:
        * **Texto A (Bitácora):** La nueva entrada para `contexto_log.md` (siempre con las 7 secciones).
        * **Texto B (Actualización README):** (Si aplica) El texto actualizado para el `README.md` si el stack o el estado cambiaron.
        * **Texto C (Contenido Wiki):** (Si aplica) El contenido de documentación estática para la `GitHub Wiki`.
7.  **Commit Único y Push (Tu Lado):**
    * **Validación Crucial:** Revisas la Bitácora (Texto A), especialmente "Archivos Modificados", y la corriges/complementas basándote en tu `git status`.
    * Añades todos tus archivos: `git add .`
    * Haces **un solo commit** con un mensaje que **"resuelva"** el Issue:
        `git commit -m "feat: Crea modelos de Veterinaria (resuelve #3)"`
    * Subes tu rama a GitHub: `git push origin feature/3-modelado-veterinaria`
8.  **Cierre de Tarea (Tu Lado y GitHub):**
    * Vas a GitHub y creas un **Pull Request** para fusionar `feature/3-modelado-veterinaria` en `develop`.
    * Al fusionar, GitHub **automáticamente cerrará el `Issue #3`** y lo moverá a la columna **`Hecho`** en `GitHub Projects`.
    * Finalmente, vas a la `Wiki` y pegas el **Texto C** (si lo hubo).

### E. Revisiones Periódicas
* Al inicio de cada semana (o cuando lo veamos necesario), dedicaremos unos minutos a revisar juntos este `README.md` para asegurar que sigue siendo 100% preciso.
