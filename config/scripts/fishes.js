// 鱼跃效果集成脚本 - 修复页脚变宽问题
(function() {
  console.log('Fish effect script loaded');
  
  function initFishEffect() {
    console.log('Initializing fish effect');
    
    // 确保jQuery已加载
    if (typeof jQuery === 'undefined') {
      console.error('jQuery is required for fish effect');
      return;
    }
    
    // 添加鱼跃效果容器到页脚
    var $footer = $("#footer");
    if ($footer.length === 0) {
      console.error('Footer element not found, trying alternative selector');
      $footer = $("footer");
    }
    
    if ($footer.length === 0) {
      console.error('Footer element not found');
      return;
    }
    
    console.log('Footer found:', $footer[0]);
    
    // 如果容器已存在，先移除
    $('#jsi-flying-fish-container').remove();
    
    // 添加容器
    $footer.append(
      '<div class="container" id="jsi-flying-fish-container"></div>'
    );
    console.log('Container added to footer');
    
    // 添加CSS样式确保容器不会影响页脚布局
    var styleId = 'fish-effect-styles';
    if (!$('#' + styleId).length) {
      var style = document.createElement('style');
      style.id = styleId;
      style.textContent = `
        #jsi-flying-fish-container {
          position: absolute;
          top: 0;
          left: 0;
          width: 100%;
          height: 100%;
          pointer-events: none;
          z-index: 0; /* 在页脚背景之上，但在页脚内容之下 */
          overflow: hidden;
        }
        #jsi-flying-fish-container canvas {
          position: absolute;
          top: 0;
          left: 0;
          width: 100%;
          height: 100%;
        }
        footer {
          position: relative !important;
          min-height: 100px; /* 确保页脚有足够高度 */
        }
        footer::before {
          content: '';
          position: absolute;
          top: 0;
          left: 0;
          width: 100%;
          height: 100%;
          background-image: var(--footer-bg); /* 保留页脚背景 */
          z-index: -1; /* 背景在最底层 */
        }
        .footer-other, .footer-flex, .footer-copyright, .footer_custom_text {
          position: relative;
          z-index: 1; /* 确保页脚内容在鱼跃效果之上 */
        }
      `;
      document.head.appendChild(style);
      console.log('CSS styles added');
    }
    
    // 加载鱼跃效果脚本
    var scriptId = 'fish-effect-script';
    if (!$('#' + scriptId).length) {
      var script = document.createElement('script');
      script.id = scriptId;
      script.src = '/config/scripts/fish.js';
      script.async = true;
      script.onload = function() {
        console.log('Fish.js loaded successfully');
      };
      script.onerror = function() {
        console.error('Failed to load fish.js');
      };
      document.body.appendChild(script);
      console.log('Fish.js script element added');
    }
  }
  
  // 使用jQuery的ready
  if (typeof jQuery !== 'undefined') {
    $(document).ready(function() {
      console.log('DOM ready, initializing fish effect');
      initFishEffect();
    });
  } else {
    // 备用方案
    if (document.readyState === 'loading') {
      document.addEventListener('DOMContentLoaded', initFishEffect);
    } else {
      initFishEffect();
    }
  }
})();
