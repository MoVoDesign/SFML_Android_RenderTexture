//
//  sfmlUtils.h
//  TacWars
//
//  Created by Lio on 08/06/16.
//  Copyright © 2016 Lio. All rights reserved.
//

#ifndef sfmlUtils_h
#define sfmlUtils_h

// SFML
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Transform.hpp>

// MVD
#include "mathUtils.hpp"

// OTHERS
#include <cassert>



namespace sfu {

  
  // all the vaQuad functions are short inlines
  
  // add a Quad centered on (x,y), of size (w,h)
  //    optional: color
  //    optional: texture (tx,ty) and (tw, th)
  // returns: insertion index;
  //
  //  0 ----- 2
  //  |
  //  |       3
  //  1       |
  //          |
  //  4 ----- 5
  //
  inline size_t vaAddQuad(sf::VertexArray& a_va, const sf::Vector2f& a_cxy, const sf::Vector2f& a_wh) {
    float hw = .5f * a_wh.x;
    float hh = .5f * a_wh.y;
    size_t i = a_va.getVertexCount();
    // 1st triangle
    a_va.append(sf::Vertex(a_cxy + sf::Vector2f(-hw, -hh))); // 0
    a_va.append(sf::Vertex(a_cxy + sf::Vector2f(-hw,  hh))); // 1
    a_va.append(sf::Vertex(a_cxy + sf::Vector2f( hw, -hh))); // 2
    // 2nd triangle
    a_va.append(sf::Vertex(a_cxy + sf::Vector2f( hw, -hh))); // 3
    a_va.append(sf::Vertex(a_cxy + sf::Vector2f(-hw,  hh))); // 4
    a_va.append(sf::Vertex(a_cxy + sf::Vector2f( hw,  hh))); // 5
    return i;
  }

  inline size_t vaAddQuad(sf::VertexArray& a_va, const sf::Transform& a_t, const sf::Vector2f& a_wh) {
    float hw = .5f * a_wh.x;
    float hh = .5f * a_wh.y;
    size_t i = a_va.getVertexCount();
    // 1st triangle
    a_va.append(sf::Vertex(a_t.transformPoint(sf::Vector2f(-hw, -hh)))); // 0
    a_va.append(sf::Vertex(a_t.transformPoint(sf::Vector2f(-hw,  hh)))); // 1
    a_va.append(sf::Vertex(a_t.transformPoint(sf::Vector2f( hw, -hh)))); // 2
    // 2nd triangle
    a_va.append(sf::Vertex(a_t.transformPoint(sf::Vector2f( hw, -hh)))); // 3
    a_va.append(sf::Vertex(a_t.transformPoint(sf::Vector2f(-hw,  hh)))); // 4
    a_va.append(sf::Vertex(a_t.transformPoint(sf::Vector2f( hw,  hh)))); // 5
    return i;
  }
  
  //--- SET GEOMETRY for EXISTING vaQuad (center, wh)
  inline void vaSetQuad(sf::VertexArray& a_va, size_t a_i, const sf::Vector2f& a_cxy, const sf::Vector2f& a_wh) {
    assert(a_i + 5 < a_va.getVertexCount());
    float hw = .5f * a_wh.x;
    float hh = .5f * a_wh.y;
    // 1st triangle
    a_va[a_i    ].position = a_cxy + sf::Vector2f(-hw, -hh);
    a_va[a_i + 1].position = a_cxy + sf::Vector2f(-hw,  hh);
    a_va[a_i + 2].position = a_cxy + sf::Vector2f( hw, -hh);
    // 2nd triangle
    a_va[a_i + 3].position = a_va[a_i + 2].position;
    a_va[a_i + 4].position = a_va[a_i + 1].position;
    a_va[a_i + 5].position = a_cxy + sf::Vector2f( hw,  hh);
  }
  
  //--- SET GEOMETRY for EXISTING vaQuad (transform, wh)
  inline void vaSetQuad(sf::VertexArray& a_va, size_t a_i, const sf::Transform& a_t, const sf::Vector2f& a_wh) {
    assert(a_i + 5 < a_va.getVertexCount());
    float hw = .5f * a_wh.x;
    float hh = .5f * a_wh.y;
    // 1st triangle
    a_va[a_i    ].position = a_t.transformPoint(sf::Vector2f(-hw, -hh));
    a_va[a_i + 1].position = a_t.transformPoint(sf::Vector2f(-hw,  hh));
    a_va[a_i + 2].position = a_t.transformPoint(sf::Vector2f( hw, -hh));
    // 2nd triangle
    a_va[a_i + 3].position = a_va[a_i + 2].position;
    a_va[a_i + 4].position = a_va[a_i + 1].position;
    a_va[a_i + 5].position = a_t.transformPoint(sf::Vector2f( hw,  hh));
  }
  
  //--- SET GEOMETRY for EXISTING vaQuad (tl, br)
  inline void vaSetQuadTLBR(sf::VertexArray& a_va, size_t a_i, const sf::Vector2f& a_tl, const sf::Vector2f& a_br) {
    assert(a_i + 5 < a_va.getVertexCount());
    // 1st triangle
    a_va[a_i    ].position = a_tl; // 0
    a_va[a_i + 1].position = sf::Vector2f(a_tl.x, a_br.y); // 1
    a_va[a_i + 2].position = sf::Vector2f(a_br.x, a_tl.y); // 2
    // 2nd triangle
    a_va[a_i + 3].position = a_va[a_i + 2].position;
    a_va[a_i + 4].position = a_va[a_i + 1].position;
    a_va[a_i + 5].position = a_br; // 5
  }
  
  //--- SET GEOMETRY for EXISTING vaQuad (tl, wh)
  inline void vaSetQuadTLWH(sf::VertexArray& a_va, size_t a_i, const sf::Vector2f& a_tl, const sf::Vector2f& a_wh) {
    assert(a_i + 5 < a_va.getVertexCount());
    // 1st triangle
    a_va[a_i    ].position = a_tl; // 0
    a_va[a_i + 1].position = sf::Vector2f(a_tl.x, a_tl.y + a_wh.y); // 1
    a_va[a_i + 2].position = sf::Vector2f(a_tl.x + a_wh.x, a_tl.y); // 2
    // 2nd triangle
    a_va[a_i + 3].position = a_va[a_i + 2].position;
    a_va[a_i + 4].position = a_va[a_i + 1].position;
    a_va[a_i + 5].position = a_tl + a_wh; // 5
  }
  
  //--- SET TEXTURE for vQuad
  inline void vaSetQuadTexture(sf::VertexArray& a_va, size_t a_i, const sf::Vector2f& a_tl, const sf::Vector2f& a_wh) {
    assert(a_i + 5 < a_va.getVertexCount());
    a_va[a_i    ].texCoords = a_tl;
    a_va[a_i + 1].texCoords = sf::Vector2f(a_tl.x, a_tl.y + a_wh.y);
    a_va[a_i + 2].texCoords = sf::Vector2f(a_tl.x + a_wh.x, a_tl.y);
    a_va[a_i + 3].texCoords = a_va[a_i + 2].texCoords;
    a_va[a_i + 4].texCoords = a_va[a_i + 1].texCoords;
    a_va[a_i + 5].texCoords = a_tl + a_wh;
  }
  
  //--- SET COLOR for vQuad
  inline void vaSetQuadColor(sf::VertexArray& a_va, size_t a_i, const sf::Color& a_c) {
    assert(a_i + 5 < a_va.getVertexCount());
    for (std::size_t i = 0; i < 6; ++i) { a_va[a_i + i].color = a_c; }
  }
  
  //---SET GRADIENT for vQuad
  inline void vaSetQuadGradientV(sf::VertexArray& a_va, size_t a_i, const sf::Color& a_c0, const sf::Color& a_c1) {
    assert(a_i + 5 < a_va.getVertexCount());
    a_va[a_i    ].color = a_c0;
    a_va[a_i + 1].color = a_c1;
    a_va[a_i + 2].color = a_c0;
    a_va[a_i + 3].color = a_va[a_i + 2].color;
    a_va[a_i + 4].color = a_va[a_i + 1].color;
    a_va[a_i + 5].color = a_c1;
  }

  //---SET GRADIENT for vQuad
  inline void vaSetQuadGradientH(sf::VertexArray& a_va, size_t a_i, const sf::Color& a_c0, const sf::Color& a_c1) {
    assert(a_i + 5 < a_va.getVertexCount());
    a_va[a_i    ].color = a_c0;
    a_va[a_i + 1].color = a_c0;
    a_va[a_i + 2].color = a_c1;
    a_va[a_i + 3].color = a_va[a_i + 2].color;
    a_va[a_i + 4].color = a_va[a_i + 1].color;
    a_va[a_i + 5].color = a_c1;
  }

  inline sf::Vector2f normalize(float a_x, float a_y)
  {
    float xxyy = a_x * a_x + a_y * a_y;
    if (xxyy == 0.f) { return sf::Vector2f(a_x, a_y); }
    float invLen = mu::invSqrt(xxyy);
    return sf::Vector2f(a_x * invLen, a_y * invLen);
  }

  inline sf::Vector2f normalize(const sf::Vector2f& a_source) { return normalize(a_source.x, a_source.y); }
  /*
  {
    float length = mu::sqrt((a_source.x * a_source.x) + (a_source.y * a_source.y));
    if (length != 0)
      return sf::Vector2f(a_source.x / length, a_source.y / length);
    else
      return a_source;
  }
  */
  
  //--- DOT product
  inline float dot(const sf::Vector2f& a_u, const sf::Vector2f& a_v)
  {
    return a_u.x * a_v.x + a_u.y * a_v.y;
  }

  
  inline float cross(const sf::Vector2f& a_u, const sf::Vector2f& a_v)
  {
    return a_u.x * a_v.y - a_u.y * a_v.x;
  }

  
  // length
  inline float length(const sf::Vector2f& a_u) {
    return mu::sqrt(a_u.x * a_u.x + a_u.y * a_u.y);
  }
  
  // length
  inline float distance2(const sf::Vector2f& a_u, const sf::Vector2f& a_v) {
    const sf::Vector2f uv(a_v - a_u);
    return uv.x * uv.x + uv.y * uv.y;
  }
  
  
  
  //--- CENTER sf::Text on current position
  inline void centerText(sf::Text& a_txt)
  {
    sf::FloatRect bd = a_txt.getLocalBounds();
    a_txt.setOrigin(bd.left + .5f * bd.width,
                      bd.top  + .5f * bd.height);
  }
  
  
}//eo-namespace sfu
#endif /* sfmlUtils_h */
