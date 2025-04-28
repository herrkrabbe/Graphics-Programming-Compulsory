#ifndef RENDERER_H
#define RENDERER_H

#include <QVulkanWindow>
#include <vector>
#include <unordered_map>
#include "Camera.h"
#include "VisualObject.h"
#include "Utilities.h"
#include "IScene.h"

class Renderer : public QVulkanWindowRenderer
{
public:
    Renderer(QVulkanWindow *w, bool msaa = false);

    //Initializes the Vulkan resources needed,
    // the buffers
    // vertex descriptions for the shaders
    // making the shaders, etc
    void initResources() override;

    //Set up resources - only MVP-matrix for now:
    void initSwapChainResources() override;

    //Empty for now - needed since we implement QVulkanWindowRenderer
    void releaseSwapChainResources() override;

    //Release Vulkan resources when program ends
    //Called by Qt
    void releaseResources() override;

    //Render the next frame
    void startNextFrame() override;

    //Get Vulkan info - just for fun
    void getVulkanHWInfo();

    std::vector<VisualObject*>& getObjects() { return mObjects; }
    std::unordered_map<std::string, VisualObject*>& getMap() { return mMap; }

protected:

    //Creates the Vulkan shader module from the precompiled shader files in .spv format
    VkShaderModule createShader(const QString &name);

	void setModelMatrix(QMatrix4x4 modelMatrix);
    void setViewProjectionMatrix();
	void setTexture(TextureHandle& textureHandle, VkCommandBuffer commandBuffer);

	void setRenderPassParameters(VkCommandBuffer commandBuffer);

    //The ModelViewProjection MVP matrix
    QMatrix4x4 mProjectionMatrix;
    //Rotation angle of the triangle
    float mRotation{ 0.0f };

    //Vulkan resources:
    QVulkanWindow* mWindow{ nullptr };
    QVulkanDeviceFunctions* mDeviceFunctions{ nullptr };

    VkDeviceMemory mBufferMemory{ VK_NULL_HANDLE };
    VkBuffer mBuffer{ VK_NULL_HANDLE };
 
    //For Uniform buffers
    VkDescriptorPool mDescriptorPool{ VK_NULL_HANDLE };
    VkDescriptorSetLayout mDescriptorSetLayout{ VK_NULL_HANDLE };
    VkDescriptorSet mDescriptorSet{ VK_NULL_HANDLE }; // [QVulkanWindow::MAX_CONCURRENT_FRAME_COUNT] { VK_NULL_HANDLE };

    //For Textures
    VkDescriptorPool mTextureDescriptorPool{ VK_NULL_HANDLE };
    VkDescriptorSetLayout mTextureDescriptorSetLayout{ VK_NULL_HANDLE };
	VkSampler mTextureSampler{ VK_NULL_HANDLE };
 
    VkPipelineCache mPipelineCache{ VK_NULL_HANDLE };
    VkPipelineLayout mPipelineLayout{ VK_NULL_HANDLE };
    VkPipeline mPipeline1{ VK_NULL_HANDLE };
    VkPipeline mPipeline2{ VK_NULL_HANDLE };

    VkQueue mGraphicsQueue{ VK_NULL_HANDLE };

private:
    friend class VulkanWindow;
	std::vector<VisualObject*> mObjects;    //All objects in the program  
    std::unordered_map<std::string, VisualObject*> mMap;    // alternativ container

    void createBuffer(VkDevice logicalDevice,
                      const VkDeviceSize uniAlign, VisualObject* visualObject,
                      VkBufferUsageFlags usage=VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);

	//Start of Uniforms and DescriptorSets
	void createVertexBuffer(const VkDeviceSize uniformAlignment, VisualObject* visualObject);
	void createIndexBuffer(const VkDeviceSize uniformAlignment, VisualObject* visualObject);
    void createUniformBuffer();
    void createDescriptorSetLayouts();
	void createDescriptorSet();
	void createDescriptorPools();
    void destroyBuffer(BufferHandle handle);

	void createTextureSampler();
    TextureHandle createTexture(const char* filename);
	TextureHandle createImage(int width, int height, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkFormat format);
	void transitionImageLayout(VkImage image, VkImageLayout oldLayout, VkImageLayout newLayout);
	void copyBufferToImage(VkBuffer buffer, VkImage image, int width, int height);
	VkImageView createImageView(VkImage image, VkFormat format);

	void destroyTexture(TextureHandle& textureHandle);

    //Texture variables

    VkSurfaceFormatKHR mSurfaceFormat{};

    //TextureHandle mTextureHandle{};
    std::map<std::string, TextureHandle> mTextureMap;

	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags requiredProperties);

	BufferHandle createGeneralBuffer(const VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);

    Camera mCamera;
    class VulkanWindow* mVulkanWindow{ nullptr };

	VkCommandBuffer beginTransientCommandBuffer();
	void endTransientCommandBuffer(VkCommandBuffer commandBuffer);

    BufferHandle mUniformBuffer{};
	void* mUniformBufferLocation{ nullptr };

    // Color shader material / shader
    struct mColorMaterial {
        VkShaderModule vertShaderModule;
        VkShaderModule fragShaderModule;
		//VkPipelineLayout pipelineLayout{ VK_NULL_HANDLE };    //also should have had a spesific pipeline layout
        VkPipeline pipeline{ VK_NULL_HANDLE };
    };

    std::map<std::string, mColorMaterial> colorMaterialMap;

    std::chrono::steady_clock::time_point lastUpdate;
    float deltaTime;
    IScene* mScene{nullptr};
};

#endif // RENDERER_H
