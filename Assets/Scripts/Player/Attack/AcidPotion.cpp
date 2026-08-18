#include "AcidPotion.h"

AcidPotion::AcidPotion()
    : m_Sprite(nullptr)
    , m_Velocity(0, 0)
    , m_Gravity(-800.0f)
    , m_LifeTime(0.0f)
    , m_MaxLifeTime(3.0f)
    , m_Active(false)
    , m_HasDealtDamage(false)
    , m_LandedState(LandedState::None)
    , m_LandedTimer(0.0f)
    , m_Damage(25)
{
}

void AcidPotion::Init(spe::Sprite* sprite)
{
    m_Sprite = sprite;
    m_Active = false;

    if (m_Sprite)
    {
        m_Sprite->SpriteRenderer.Render = false;
        m_Sprite->Collider.Exist = true;
        m_Sprite->Collider.IsSolid = false;
        m_Sprite->Collider.Controller = true;
        m_Sprite->Physicsbody.Exist = false;
        m_Sprite->Collider.Width = spe::Vector2(-5.0f, 5.0f);
        m_Sprite->Collider.Height = spe::Vector2(-5.0f, 5.0f);

        // weird fix but sometimes the texture isnt properly loaded causing
        // the texture to be black squares instead of the real texture, so you have to re-set it again
        if (m_Sprite->Particles.Exist)
        {
            std::string texPath = m_Sprite->Particles.GetTexturePath();
            if (!texPath.empty())
            {
                m_Sprite->Particles.SetTexturePath(texPath);
            }
        }
    }
}

void AcidPotion::Launch(const spe::Vector2& startPos, const spe::Vector2& targetPos, float speed)
{
    if (!m_Sprite) {
        return;
    }

    m_Active = true;
    m_HasDealtDamage = false;
    m_LandedState = LandedState::None;
    m_LandedTimer = 0.0f;
    m_LifeTime = 0.0f;

    m_Sprite->Transform.SetPosition(startPos);
    m_Sprite->SpriteRenderer.Render = true;

    if (m_Sprite->Particles.Exist)
    {
        m_Sprite->Particles.Play();
    }

    spe::Vector2 direction = targetPos - startPos;
    float distance = direction.Length();

    if (distance > 0.001f)
    {
        direction.Normalize();
    }
    else
    {
        direction = spe::Vector2(1.0f, 0.0f); // default to right if no direction
    }

    float arcHeight = std::min(distance * 0.5f, 300.0f);

    m_Velocity.X = direction.X * speed;
    m_Velocity.Y = (direction.Y * speed * 0.5f) + arcHeight;
}

void AcidPotion::Update()
{
    if (!m_Sprite) {
        return;
    }

    float dt = spe::Time::s_DeltaTime;

    if (m_LandedState != LandedState::None)
    {
        m_LandedTimer -= dt;

        if (m_LandedState == LandedState::Lingering && m_LandedTimer <= 0.0f)
        {
            if (m_Sprite->Particles.Exist)
            {
                m_Sprite->Particles.Stop();
            }
            m_LandedState = LandedState::FadingOut;
            m_LandedTimer = 1.5f;
        }
        else if (m_LandedState == LandedState::FadingOut && m_LandedTimer <= 0.0f)
        {
            m_Sprite->Transform.SetPosition(spe::Vector2(-10000, -10000));
            m_LandedState = LandedState::None;
        }
        return;
    }

    if (!m_Active) {
        return;
    }

    m_LifeTime += dt;

    // check lifetime
    if (m_LifeTime >= m_MaxLifeTime)
    {
        Deactivate();
        return;
    }

    m_Velocity.Y += m_Gravity * dt;

    spe::Vector2 currentPos = m_Sprite->Transform.GetPosition();
    spe::Vector2 newPos = spe::Vector2(
        currentPos.X + m_Velocity.X * dt,
        currentPos.Y + m_Velocity.Y * dt
    );
    m_Sprite->Transform.SetPosition(newPos);

    // skip collision check to avoid player
    if (m_LifeTime < 0.1f) {
        return;
    }

    // Enemy collision is handled by PlayerAttack::CheckEnemyHits()
    for (const auto& pair : m_Sprite->Collider.CollidedSprites)
    {
        spe::Sprite* other = pair.second;
        if (other && other->Collider.IsSolid &&
            other->Tag != "Player" &&
            other->Tag != "Potion"){
            OnLand();
            return;
        }
    }
}

void AcidPotion::OnLand()
{
    m_Active = false;
    m_LandedState = LandedState::Lingering;
    m_LandedTimer = 0.5f;

    if (m_Sprite)
    {
        // hide the potion sprite but keep it at landing position for particles
        m_Sprite->SpriteRenderer.Render = false;
    }
}

void AcidPotion::Deactivate()
{
    m_Active = false;
    m_LandedState = LandedState::None;
    if (m_Sprite)
    {
        if (m_Sprite->Particles.Exist)
        {
            m_Sprite->Particles.Stop();
        }
        m_Sprite->SpriteRenderer.Render = false;
        m_Sprite->Transform.SetPosition(spe::Vector2(-10000, -10000));
    }
}

